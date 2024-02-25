#pragma once

#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Sprite.hpp"

class Renderer {
public:
    static void render(const GLuint& vao, const Texture& texture, const ShaderProgram& shader);
    static void clearColor(float r, float g, float b, float a);
    static void clear();
    static void viewport(const GLint x, const GLint y, const GLsizei width, const GLsizei height);

private:
    Renderer() = delete;
};