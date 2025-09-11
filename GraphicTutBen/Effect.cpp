#include "Effect.h"

Effect::Effect(glm::vec2 position, EFFECT effectType) :
	m_fireFadeSpeed(10),
	m_enemyDestroyedFadeSpeed(10)

{
	m_color.r = 255;
	m_color.g = 255;
	m_color.b = 255;
	m_color.a = 255;

	m_position = position;

	switch (effectType)
	{
	case EFFECT::PLAYER_FIRE:
		m_texture = Engine::ResourceManager::getTexture("Textures/PNG/Effects/fire17.png");
		break;

	case EFFECT::ENEMY_DESTROYED_PHASE_1:
		m_texture = Engine::ResourceManager::getTexture("Textures/PNG/Damage/playerShip1_damage3.png");
		break;

	case EFFECT::ENEMY_DESTROYED_PHASE_2:
		m_texture = Engine::ResourceManager::getTexture("Textures/PNG/Damage/playerShip1_damage2.png");
		break;

	case EFFECT::ENEMY_DESTROYED_PHASE_3:
		m_texture = Engine::ResourceManager::getTexture("Textures/PNG/Damage/playerShip1_damage1.png");
		break;

	default:

		break;
	}
}

void Effect::draw(Engine::SpriteBatch& spriteBatch)
{
	glm::vec4 posAndSize = glm::vec4(m_position.x, m_position.y, m_texture.width * 2, m_texture.height * 2);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	spriteBatch.draw(posAndSize, uv, m_texture.id, 0.0f, m_color);
}

void Effect::updateFireEffect(float deltaTime)
{
	m_color.a -= m_fireFadeSpeed * deltaTime;
}

void Effect::updateDestroyedEffect()
{
	m_color.a -= m_enemyDestroyedFadeSpeed;
}