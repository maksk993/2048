#include "Sprite.hpp"

Sprite::Sprite(std::shared_ptr<Texture> pTexture, std::shared_ptr<ShaderProgram> pShaderProgram, 
	const glm::vec2& position, 
	const glm::vec2& size, 
	const float rotation,
	std::array<float, 8>& userTexCoords,
	std::array<float, 8>& userVertCoords)
	: m_pTexture(std::move(pTexture)), m_pShaderProgram(std::move(pShaderProgram)), 
	m_position(position), m_size(size), m_rotation(rotation)
{
	m_pVAO = std::make_shared<VAO>();
	m_VAO = m_pVAO->getID();

	m_pVBO_vector.emplace_back(std::make_shared<VBO>(std::move(userVertCoords)));
	m_pVAO->addBuffer(m_pVBO_vector.back()->getID());

	m_pVBO_vector.emplace_back(std::make_shared<VBO>(std::move(userTexCoords)));
	m_pVAO->addBuffer(m_pVBO_vector.back()->getID());
	
	VBO::unbind();
	VAO::unbind();
}

void Sprite::render() const {
	glm::mat4x4 model(1.f);

	model = glm::translate(model, glm::vec3(m_position, 0.f));
	model = glm::translate(model, glm::vec3(0.5f * m_size.x, 0.5f * m_size.y, 0.f));
	model = glm::rotate(model, glm::radians(m_rotation), glm::vec3(0.f, 0.f, 1.f));
	model = glm::translate(model, glm::vec3(-0.5f * m_size.x, -0.5f * m_size.y, 0.f));
	model = glm::scale(model, glm::vec3(m_size, 1.f));
	m_pShaderProgram->setMatrix4("modelMat", model);

	Renderer::render(m_VAO, *m_pTexture, *m_pShaderProgram);
}

void Sprite::setPosition(const glm::vec2& position) {
	m_position = position;
}

void Sprite::setSize(const glm::vec2& size) {
	m_size = size;
}

void Sprite::setRotation(const float rotation) {
	m_rotation = rotation;
}