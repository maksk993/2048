#pragma once

#include "glad/glad.h"
#include <array>

class VBO {
public:
	VBO(const std::array<GLfloat, 8>& userCoords);
	~VBO();

	VBO(const VBO&) = delete;
	VBO& operator=(const VBO&) = delete;

	GLuint getID() const;
	static void bind(const GLuint& id);
	static void unbind();

private:
	GLuint m_ID;
};