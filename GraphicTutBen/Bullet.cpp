#include "Bullet.h"

Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float speed, int lifeTime, int damage) :
	m_position(position),
	m_direction(direction),
	m_speed(speed),
	m_lifeTime(lifeTime),
	m_damage(damage)
{}

void Bullet::draw(Engine::SpriteBatch& spriteBatch)
{
	Engine::ColorRGBA8 color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	m_texture = Engine::ResourceManager::getTexture("Textures/PNG/Lasers/laserBlue01.png");

	glm::vec4 posAndSize = glm::vec4(m_position.x, m_position.y, m_texture.width, m_texture.height);
	const glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	spriteBatch.draw(posAndSize, uv, m_texture.id, 0.0f, color);
}

void Bullet::update(int screenHeight, float deltaTime)
{
	m_position += m_direction * m_speed * deltaTime;
	m_lifeTime--;

	if (screenHeight / 2 < m_position.y)
	{
		m_lifeTime = 0;
	}
}

bool Bullet::colideWithAgent(Agent& agent)
{
	glm::vec2 enemyPosition = agent.getPosition();
	int enemyWidth = agent.getWidth();
	int enemyHeight = agent.getHeigh();

	if (m_position.x > enemyPosition.x && m_position.x < enemyPosition.x + enemyWidth
		&& m_position.y > enemyPosition.y && m_position.y < enemyPosition.y + enemyHeight)
	{
		return true;
	}

	return false;
}