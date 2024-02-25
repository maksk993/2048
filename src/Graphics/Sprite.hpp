#pragma once

#include "Renderer.hpp"
#include "VAO.hpp"
#include "VBO.hpp"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <array>

class Sprite {
public:
	Sprite(std::shared_ptr<Texture> pTexture, std::shared_ptr<ShaderProgram> pShaderProgram,
		const glm::vec2& position = glm::vec2(0.f),
		const glm::vec2& size = glm::vec2(1.f),
		const float rotation = 0.f,
		std::array<float, 8>& userTexCoords = std::array<float, 8>{0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f},
		std::array<float, 8>& userVertCoords = std::array<float, 8>{0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f}
	);
	~Sprite() = default;

	Sprite(const Sprite&) = delete;
	Sprite& operator=(const Sprite&) = delete;

	void render() const;
	void setPosition(const glm::vec2& position);
	void setSize(const glm::vec2& size);
	void setRotation(const float rotation);

private:
	std::shared_ptr<Texture> m_pTexture;
	std::shared_ptr<ShaderProgram> m_pShaderProgram;
	glm::vec2 m_position;
	glm::vec2 m_size;
	float m_rotation;

	std::shared_ptr<VAO> m_pVAO;
	GLuint m_VAO;
	std::vector <std::shared_ptr<VBO>> m_pVBO_vector;
};