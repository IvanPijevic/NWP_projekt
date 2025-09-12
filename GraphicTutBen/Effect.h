#ifndef EFFECT_H
#define EFFECT_H

#include <glm/glm.hpp>
#include <Engine/SpriteBatch.h>
#include <Engine/ResourceManager.h>

enum class EFFECT
{
	PLAYER_FIRE,

	ENEMY_FIRE, 

	ENEMY_DESTROYED_PHASE_1,
	ENEMY_DESTROYED_PHASE_2,
	ENEMY_DESTROYED_PHASE_3,

	PLAYER_DESTROYED
};

class Effect
{
public:
	Effect(glm::vec2 position, EFFECT effectType);

	void draw(Engine::SpriteBatch& spriteBatch);
	void updateFireEffect(float deltaTime);
	void updateDestroyedEffect();

	//Getters
	GLubyte getColorA() const { return this->m_color.a; }
	int getFadeSpeed() const { return this->m_fireFadeSpeed; }
	glm::vec2 getDimension() const { return glm::vec2(m_texture.width, m_texture.height); }
	glm::vec2 getPosition() const { return this->m_position; }

private:
	Engine::Texture m_texture;
	Engine::ColorRGBA8 m_color;

	int m_fireFadeSpeed;
	int m_enemyDestroyedFadeSpeed;

	glm::vec2 m_position;

	EFFECT m_effect;
};

#endif