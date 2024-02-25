#include "VAO.hpp"

VAO::VAO() {
	glGenVertexArrays(1, &m_ID);
	bind(m_ID);
}

VAO::~VAO() {
	glDeleteVertexArrays(1, &m_ID);
}

GLuint VAO::getID() const {
	return m_ID;
}

void VAO::addBuffer(const GLuint& vbo_id) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glEnableVertexAttribArray(attribIndex);
	glVertexAttribPointer(attribIndex++, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void VAO::bind(const GLuint& id) {
	glBindVertexArray(id);
}

void VAO::unbind() {
	glBindVertexArray(0);
}