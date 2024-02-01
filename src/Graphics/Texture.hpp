#pragma once
#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include <glad/glad.h>
#include <iostream>
#include <string>

#include "stb_image.h"

class Texture {
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
    GLenum m_filter;
    GLenum m_wrapmode;
    GLenum m_mode;

    GLuint m_ID;

    unsigned int m_width;
    unsigned int m_height;

    std::string load(const std::string& path);
    void createTexture(const unsigned int channels, const unsigned char* pixels);
};

#endif // !__TEXTURE_HPP__