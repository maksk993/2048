#pragma once

#include "glad/glad.h"
#include "VBO.hpp"
#include <vector>

class VAO {
public:
	VAO();
	~VAO();

	VAO(const VAO&) = delete;
	VAO& operator=(const VAO&) = delete;

	GLuint getID() const;
	void addBuffer(const GLuint& vbo_id);
	static void bind(const GLuint& id);
	static void unbind();

private:
	GLuint m_ID;
	GLuint attribIndex = 0;
};