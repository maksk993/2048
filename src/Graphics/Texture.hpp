#pragma once

#include "stb_image.h"
#include <glad/glad.h>

#include <iostream>
#include <string>

class Texture { // Работа с текстурами
public:
	Texture(const std::string& texturePath,
        const unsigned int channels = 4,
        const GLenum filter = GL_LINEAR,
        const GLenum wrapmode = GL_CLAMP_TO_EDGE);
    ~Texture();
    
    Texture() = delete;
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    Texture(Texture&&) noexcept;
    Texture& operator=(Texture&&) noexcept;

    GLuint getID() const;
    void bind() const;

private:
    GLuint m_ID = 0;
    GLenum m_filter;
    GLenum m_wrapmode;
    GLenum m_mode;

    unsigned int m_width;
    unsigned int m_height;

    std::string load(const std::string& path);
    void createTexture(const unsigned int channels, const unsigned char* pixels);
};