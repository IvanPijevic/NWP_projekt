#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>

#include <Engine/SpriteBatch.h>
#include <Engine/ResourceManager.h>
#include <Engine/InputManager.h>

#include "Agent.h"
#include "Weapon.h"
#include "Bullet.h"
#include "Effect.h"
#include "BackgroundElements.h"

class Player : public Agent
{
public:
	void addWeapon(Weapon weapon);
	void init(float speed, int health, int lives, glm::vec2 position, Engine::InputManager* input, std::vector<Bullet>* bullets);
	void update(Engine::InputManager& input, int screenWidth, int screenHeight, float deltaTime);
	void draw(Engine::SpriteBatch& spriteBatch);

	bool colideWithEnemy(Agent* agent);
	bool colideWithStar(BackgroundElements* star, int index);

	glm::vec2 getPlayerPosition() { return this->m_position; }
	std::vector<Effect> getEffectVec()  { return m_effects; }
	int getPlayerLives() { return this->m_lives; }
	glm::vec2 getPlayerStartPosition() { return this->m_playerStartPosition; }

	void setPlayerLives(int lives) { m_lives = lives; }
	void setPlayerPosition(glm::vec2 position) { m_position = position; }

private:
	std::vector<Weapon> m_weapons;
	std::vector<Effect> m_effects;

	int m_weaponNumber = -1;
	int m_lives;

	glm::vec2 m_playerStartPosition = glm::vec2(0.0f, -300.0f);

	std::vector<Bullet>* m_bullets;

	Engine::InputManager* m_input;
	Engine::ColorRGBA8 m_color;
};

#endif