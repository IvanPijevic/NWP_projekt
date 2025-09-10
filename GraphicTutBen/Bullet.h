#ifndef BULLET_H
#define BULLET_H

#include <glm/glm.hpp>
#include <Engine/SpriteBatch.h>
#include <Engine/ResourceManager.h>

#include "Agent.h"
#include "Enemy.h"

class Agent;
class Enemy;

class Bullet
{
public:
	Bullet(glm::vec2 position, glm::vec2 direction, float speed, int lifeTime, int damage);
	~Bullet();

	void draw(Engine::SpriteBatch& spriteBatch);
	void update(int screenHeight, float deltaTime);

	bool colideWithAgent(Agent& agent);

	int getLifeTime() { return m_lifeTime; }
	int getDamage() { return m_damage; }
	glm::vec2 getPosition() { return m_position; }
	glm::vec2 getDimension() { return glm::vec2(m_texture.width, m_texture.height); }
	float getWidth() { return m_texture.width; }
	float getHeight() { return m_texture.height; }

private:
	glm::vec2 m_position;
	glm::vec2 m_direction;

	float m_speed;
	int m_lifeTime;
	int m_damage;

	Engine::Texture m_texture;
};

#endif