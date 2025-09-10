#ifndef AGENT_H
#define AGENT_H

#include <Engine/SpriteBatch.h>
#include <Engine/ResourceManager.h>

class Agent
{
public:
	Agent();
	virtual ~Agent();

	glm::vec2 getPosition() const { return m_position; }
	glm::vec2 getDimension() const { return glm::vec2(m_texture.width, m_texture.height); }
	int getWidth() const { return m_texture.width; }
	int getHeigh() const { return m_texture.height; }
	int getHP() { return m_healthPoints; }

	void setHealthPoints(int healthPoints) { m_healthPoints = healthPoints; }

protected:
	glm::vec2 m_position;
	Engine::Texture m_texture;

	float m_speed;

	int m_healthPoints;
	int m_manaPoints;
	int m_shieldPoints;
};

#endif