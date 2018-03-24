#include "Mesh.h"

Mesh::Mesh(void) {
	for (int i = 0; i < MAX_BUFFER; ++i) {
		bufferObject[i] = 0;
	}
	glGenVertexArrays(1, &arrayObject);

	numVertices = 0;
	texture = 0;
	numIndices = 0;

	indices = NULL;
	vertices = NULL;
	colours = NULL;
	type = GL_TRIANGLES;
	textureCoords = NULL;
}

Mesh ::~Mesh(void) {
	glDeleteVertexArrays(1, &arrayObject);
	glDeleteBuffers(MAX_BUFFER, bufferObject);
	glDeleteTextures(1, &texture);
	
	delete[] vertices;
	delete[] colours;
	delete[] textureCoords;
	delete[] indices;

}

Mesh * Mesh::GenerateCube() {
	Mesh * m = new Mesh();
	m->numVertices = 36;

	m -> vertices = new Vector3[m->numVertices];
	m->vertices[0] = Vector3(-1.0f, -1.0f, -1.0f);
	m->vertices[1] = Vector3(-1.0f, -1.0f, 1.0f);
	m->vertices[2] = Vector3(-1.0f, 1.0f, 1.0f);
	m->vertices[3] = Vector3(1.0f, 1.0f, -1.0f);
	m->vertices[4] = Vector3(-1.0f, -1.0f, -1.0f);
	m->vertices[5] = Vector3(-1.0f, 1.0f, -1.0f);
	m->vertices[6] = Vector3(1.0f, -1.0f, 1.0f);
	m->vertices[7] = Vector3(-1.0f, -1.0f, -1.0f);
	m->vertices[8] = Vector3(1.0f, -1.0f, -1.0f);
	m->vertices[9] = Vector3(1.0f, 1.0f, -1.0f);
	m->vertices[10] = Vector3(1.0f, -1.0f, -1.0f);
	m->vertices[11] = Vector3(-1.0f, -1.0f, -1.0f);
	m->vertices[12] = Vector3(-1.0f, -1.0f, -1.0f);
	m->vertices[13] = Vector3(-1.0f, 1.0f, 1.0f);
	m->vertices[14] = Vector3(-1.0f, 1.0f, -1.0f);
	m->vertices[15] = Vector3(1.0f, -1.0f, 1.0f);
	m->vertices[16] = Vector3(-1.0f, -1.0f, 1.0f);
	m->vertices[17] = Vector3(-1.0f, -1.0f, -1.0f);
	m->vertices[18] = Vector3(-1.0f, 1.0f, 1.0f);
	m->vertices[19] = Vector3(-1.0f, -1.0f, 1.0f);
	m->vertices[20] = Vector3(1.0f, -1.0f, 1.0f);
	m->vertices[21] = Vector3(1.0f, 1.0f, 1.0f);
	m->vertices[22] = Vector3(1.0f, -1.0f, -1.0f);
	m->vertices[23] = Vector3(1.0f, 1.0f, -1.0f);
	m->vertices[24] = Vector3(1.0f, -1.0f, -1.0f);
	m->vertices[25] = Vector3(1.0f, 1.0f, 1.0f);
	m->vertices[26] = Vector3(1.0f, -1.0f, 1.0f);
	m->vertices[27] = Vector3(1.0f, 1.0f, 1.0f);
	m->vertices[28] = Vector3(1.0f, 1.0f, -1.0f);
	m->vertices[29] = Vector3(-1.0f, 1.0f, -1.0f);
	m->vertices[30] = Vector3(1.0f, 1.0f, 1.0f);
	m->vertices[31] = Vector3(-1.0f, 1.0f, -1.0f);
	m->vertices[32] = Vector3(-1.0f, 1.0f, 1.0f);
	m->vertices[33] = Vector3(1.0f, 1.0f, 1.0f);
	m->vertices[34] = Vector3(-1.0f, 1.0f, 1.0f);
	m->vertices[35] = Vector3(1.0f, -1.0f, 1.0f);

	m -> textureCoords = new Vector2[m -> numVertices];
	m->textureCoords[0] = Vector2(0, 1);
	m->textureCoords[1] = Vector2(1, 1);
	m->textureCoords[2] = Vector2(1, 0);
	m->textureCoords[3] = Vector2(0, 0);
	m->textureCoords[4] = Vector2(0, 1);
	m->textureCoords[5] = Vector2(1, 1);
	m->textureCoords[6] = Vector2(1, 0);
	m->textureCoords[7] = Vector2(0, 0);
	m->textureCoords[8] = Vector2(0, 1);
	m->textureCoords[9] = Vector2(1, 1);
	m->textureCoords[10] = Vector2(1, 0);
	m->textureCoords[11] = Vector2(0, 0);
	m->textureCoords[12] = Vector2(0, 1);
	m->textureCoords[13] = Vector2(1, 1);
	m->textureCoords[14] = Vector2(1, 0);
	m->textureCoords[15] = Vector2(0, 0);
	m->textureCoords[16] = Vector2(0, 1);
	m->textureCoords[17] = Vector2(1, 1);
	m->textureCoords[18] = Vector2(1, 0);
	m->textureCoords[19] = Vector2(0, 0);
	m->textureCoords[20] = Vector2(0, 1);
	m->textureCoords[21] = Vector2(1, 1);
	m->textureCoords[22] = Vector2(1, 0);
	m->textureCoords[23] = Vector2(0, 0);
	m->textureCoords[24] = Vector2(0, 0);
	m->textureCoords[25] = Vector2(0, 0);
	m->textureCoords[26] = Vector2(0, 0);
	m->textureCoords[27] = Vector2(0, 0);
	m->textureCoords[28] = Vector2(0, 0);
	m->textureCoords[29] = Vector2(0, 0);
	m->textureCoords[30] = Vector2(0, 0);
	m->textureCoords[31] = Vector2(0, 0);
	m->textureCoords[32] = Vector2(0, 0);
	m->textureCoords[33] = Vector2(0, 0);
	m->textureCoords[34] = Vector2(0, 0);
	m->textureCoords[35] = Vector2(0, 0);

	m -> BufferData();

	return m;
}


void Mesh::BufferData() {
	glBindVertexArray(arrayObject);
	glGenBuffers(1, &bufferObject[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, bufferObject[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector3),
		vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(VERTEX_BUFFER);

	if (textureCoords) { // This bit is new !
		glGenBuffers(1, &bufferObject[TEXTURE_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[TEXTURE_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector2),
			textureCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TEXTURE_BUFFER);
	}

	if (indices) {
		glGenBuffers(1, &bufferObject[INDEX_BUFFER]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
			bufferObject[INDEX_BUFFER]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint),
			indices, GL_STATIC_DRAW);
	}

	if (colours) { // Just in case the data has no colour attribute ...
		glGenBuffers(1, &bufferObject[COLOUR_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[COLOUR_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector4),
			colours, GL_STATIC_DRAW);
		glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(COLOUR_BUFFER);
	}
	glBindVertexArray(0);
}

void Mesh::Draw() {
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(arrayObject);

	if (bufferObject[INDEX_BUFFER]) {
		glDrawElements(type, numIndices, GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(type, 0, numVertices);
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

}

