#include "VBO.hpp"

VBO::VBO(const std::array<GLfloat, 8>& userCoords) {
	GLfloat coords[8];
	for (int i = 0; i < 8; i++) {
		coords[i] = userCoords[i];
	};

	glGenBuffers(1, &m_ID);
	bind(m_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coords), &coords, GL_STATIC_DRAW);
}

VBO::~VBO() {
	glDeleteBuffers(1, &m_ID);
}

GLuint VBO::getID() const {
	return m_ID;
}

void VBO::bind(const GLuint& id) {
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
