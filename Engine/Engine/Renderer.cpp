#include "Renderer.h"





Renderer::Renderer(Window &parent) : OGLRenderer(parent)	{

	currentShader = new Shader("../../Shaders/TexturedVertex.glsl",
		"../../Shaders/TexturedFragment.glsl");

	if(!currentShader->LinkProgram()) {
		return;
	}

	projMatrix = Matrix4::Perspective(1.0f, 100000.0f,
		(float)width / (float)height, 55.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);

	error = FT_Init_FreeType(&library);
	if (error) { cout << "ERROR: initialising FreeType library" << endl; }
	
	error = FT_New_Face(library, "../../Fonts/micross.ttf", 0, &font);
	if (error) { cout << "ERROR: loading font file" << endl; }

	FT_Set_Pixel_Sizes(
		font,   /* handle to face object */
		UI_FONT_PIXELS,      /* pixel_width           */
		0);   /* pixel_height          */



	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	color = new float[UI_WIDTH*UI_HEIGHT*4];

	ui->SetTexture(texID);

	clearUI();

	init = true;
}
Renderer::~Renderer(void)	{
	
}


void Renderer::RenderScene()
{
	SwapBuffers();
	glClearDepth(1.0f);
	glClearColor(0.2f,0.2f,0.2f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	glUseProgram(currentShader->GetProgram());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	viewMatrix = player->getCamera().BuildViewMatrix();

	for (vector<Entity *>::iterator it = entities.begin(); it != entities.end(); ++it) {

		modelMatrix = (**it).getModelMatrix();
		
		UpdateShaderMatrices();
		(**it).getMesh()->Draw();
	}


	modelMatrix = Matrix4::Scale(Vector3(UI_WIDTH / 2, UI_HEIGHT / 2, 1));
	viewMatrix.ToIdentity();
	Matrix4 temp = projMatrix;
	projMatrix = Matrix4::Orthographic(-1.001, 1000, -UI_WIDTH / 2, UI_WIDTH / 2, -UI_HEIGHT / 2, UI_HEIGHT / 2);
	UpdateShaderMatrices();
	ui->Draw();
	projMatrix = temp;

	glUseProgram(0);
	
}

//LAGGY
void Renderer::drawText(string s, int sX, int sY, Vector3 colour)
{
	FT_GlyphSlot  slot = font->glyph;
	FT_UInt glyphIndex;
	int yVal;

	for (int i = 0; i < s.length(); ++i) {
		/* retrieve glyph index from character code */
		glyphIndex = FT_Get_Char_Index(font, s[i]);

		/* load glyph image into the slot (erase previous one) */
		FT_Load_Glyph(font, glyphIndex, FT_LOAD_DEFAULT);

		/* convert to an anti-aliased bitmap */
		FT_Render_Glyph(font->glyph, FT_RENDER_MODE_NORMAL);

		

		for (int y = 0; y < slot->bitmap.rows; ++y) {
			for (int x = 0; x < slot->bitmap.width; ++x) {
				yVal = sY + y + (UI_FONT_PIXELS - slot->bitmap.rows);
				if (sX + x >= UI_WIDTH || yVal < 0 || sX + x < 0 || yVal >= UI_HEIGHT) {
					break;
				}
				color[(yVal*UI_WIDTH + sX + x) * 4 - 4] = colour.x;
				color[(yVal*UI_WIDTH + sX + x) * 4 - 3] = colour.y;
				color[(yVal*UI_WIDTH + sX + x) * 4 - 2] = colour.z;
				color[(yVal*UI_WIDTH + sX + x) * 4 - 1] = float(unsigned char(slot->bitmap.buffer[y*slot->bitmap.width + x])) / 256;
			}
			cout << endl;
		}

		sX += slot->bitmap.width + LETTER_GAP_PIXELS;
	}

	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, UI_WIDTH, UI_HEIGHT, 0, GL_RGBA, GL_FLOAT, color);
}

void Renderer::drawCrosshair(Vector4 colour, Crosshair c)
{
	switch (c) {
	case (CROSSHAIR_DEFAULT):
		int w,h;
		for (int i = -15; i < 15; ++i) {
			h = w = UI_HEIGHT * UI_WIDTH * 4 / 2 + UI_WIDTH * 4 / 2;	//Centre
			
			(i < 0) ? (w -= 4 * (abs(i+1) + 5)) : (w += 4 * (i + 5));
			(i < 0) ? (h -= 4 * UI_WIDTH * (abs(i+1) + 5)) : (h += 4 * UI_WIDTH * (i + 5));

			color[w    ] = colour.x;
			color[w + 1] = colour.y;
			color[w + 2] = colour.z;
			color[w + 3] = colour.w;

			color[h    ] = colour.x;
			color[h + 1] = colour.y;
			color[h + 2] = colour.z;
			color[h + 3] = colour.w;

		}

		w = UI_HEIGHT * UI_WIDTH * 4 / 2 + UI_WIDTH * 4 / 2;

		color[w    ] = colour.x;
		color[w + 1] = colour.y;
		color[w + 2] = colour.z;
		color[w + 3] = colour.w;

		break;
	}


	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, UI_WIDTH, UI_HEIGHT, 0, GL_RGBA, GL_FLOAT, color);
}

void Renderer::clearUI(int sx, int sy, int width, int height)
{
	for (int i = sy * UI_WIDTH * sx * 4; i < sy * (UI_WIDTH + height) * sx * 4; i += UI_WIDTH) {
		memset(color+i, 0, width*4);
	}

	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, UI_WIDTH, UI_HEIGHT, 0, GL_RGBA, GL_FLOAT, color);
}

