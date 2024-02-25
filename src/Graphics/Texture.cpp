#include "Texture.hpp"

Texture::Texture(const std::string& texturePath, const unsigned int channels, const GLenum filter, const GLenum wrapmode)
	: m_filter(filter), m_wrapmode(wrapmode)
{
	std::string errorCode = load(texturePath);
	if (errorCode != "0") std::cerr << "Can't create texture: " << texturePath << std::endl;
}

Texture::~Texture() {
	glDeleteTextures(1, &m_ID);
}

Texture::Texture(Texture&& other) noexcept {
	m_ID = other.m_ID;
	m_filter = other.m_filter;
	m_wrapmode = other.m_wrapmode;
	m_mode = other.m_mode;
	m_width = other.m_width;
	m_height = other.m_height;

	other.m_ID = other.m_width = other.m_height = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept {
	if (this != &other) {
		glDeleteTextures(1, &m_ID);
		m_ID = other.m_ID;
		m_filter = other.m_filter;
		m_wrapmode = other.m_wrapmode;
		m_mode = other.m_mode;
		m_width = other.m_width;
		m_height = other.m_height;

		other.m_ID = other.m_width = other.m_height = 0;
	}
	return *this;
}

GLuint Texture::getID() const {
	return m_ID;
}

void Texture::bind() const {
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

std::string Texture::load(const std::string& path) {
	int channels = 0;
	int width = 0;
	int height = 0;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* pixels = stbi_load(path.c_str(), &width, &height, &channels, 0);

	m_width = width;
	m_height = height;

	if (!pixels) {
		std::cerr << "Can't load texture: " << path << std::endl;
		return "-1";
	}

	createTexture(channels, pixels);
	stbi_image_free(pixels);

	return "0";
}

void Texture::createTexture(const unsigned int channels, const unsigned char* pixels) {
	switch (channels) {
	case 3:
		m_mode = GL_RGB;
		break;
	case 4:
		m_mode = GL_RGBA;
		break;
	default:
		m_mode = GL_RGBA;
		break;
	}

	glGenTextures(1, &m_ID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, m_mode, m_width, m_height, 0, m_mode, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapmode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapmode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filter);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}