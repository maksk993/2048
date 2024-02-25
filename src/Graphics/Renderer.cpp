#include "Renderer.hpp"

void Renderer::render(const GLuint& vao, const Texture& texture, const ShaderProgram& shader) {
	shader.use();
	VAO::bind(vao);

	glActiveTexture(GL_TEXTURE0);
	texture.bind();

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Renderer::clearColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}

void Renderer::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::viewport(const GLint x, const GLint y, const GLsizei width, const GLsizei height) {
	glViewport(x, y, width, height);
}
