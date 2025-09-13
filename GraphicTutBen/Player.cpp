#include "Player.h"

void Player::addWeapon(Weapon weapon)
{
	m_weapons.push_back(weapon);
	m_weaponNumber = 0;

}

void Player::init(float speed, int health, int lives, glm::vec2 position, Engine::InputManager* input, std::vector<Bullet>* bullets)
{
	m_speed = speed;
	m_position = position;
	m_input = input;
	m_bullets = bullets;
	m_healthPoints = health;
	m_lives = lives;

	m_texture = Engine::ResourceManager::getTexture("Textures/PNG/playerShip1_blue.png");
	
	m_color = Engine::ColorRGBA8(255, 255, 255, 255);
}

void Player::update(Engine::InputManager& input, int screenWidth, int screenHeight, float deltaTime)
{
	if (m_input->isKeyDown(SDLK_w))
	{
		m_position.y += m_speed * deltaTime;
		if (m_position.y > screenHeight / 2 - m_texture.height)
		{
			m_position.y = screenHeight / 2 - m_texture.height;
		}
	}
	if (m_input->isKeyDown(SDLK_s))
	{
		m_position.y -= m_speed * deltaTime;
		if (m_position.y < -(screenHeight / 2))
		{
			m_position.y = -screenHeight / 2;
		}
	}
	if (m_input->isKeyDown(SDLK_a))
	{
		m_position.x -= m_speed * deltaTime;
		if (m_position.x < -(screenWidth / 2))
		{
			m_position.x = -screenWidth / 2;
		}
	}
	if (m_input->isKeyDown(SDLK_d))
	{
		m_position.x += m_speed * deltaTime;
		if (m_position.x > screenWidth / 2 - m_texture.width)
		{
			m_position.x = screenWidth / 2 - m_texture.width;
		}
	}

	
	if (m_input->isKeyDown(SDLK_1) && m_weapons.size() >= 0)
	{
		m_weaponNumber = 0;
	}
	else if (m_input->isKeyDown(SDLK_2) && m_weapons.size() >= 1)
	{
		m_weaponNumber = 1;
	}

	//First weapon
	//Default weapon
	if (m_weaponNumber == 0)
	{
		glm::vec2 pos[10];
		pos[0] = m_position;
		pos[0].x += m_texture.width / 2 - 4;  //Center fire position
		pos[0].y += m_texture.height;
		m_weapons[m_weaponNumber].update(m_input->isKeyDown(SDLK_SPACE), m_weapons[m_weaponNumber].getBulletsPerShoot(), pos, glm::vec2(0.0f, 1.0f), *m_bullets, deltaTime);
		
		//Add fire effects
		if (m_weapons[m_weaponNumber].getIsFired())
		{
			pos[0].x -= 9;  //Center effect position

			int bullets = m_weapons[m_weaponNumber].getBulletsPerShoot();
			std::for_each_n(std::execution::seq,m_effects.end(),bullets,[&](Effect&) 
				{
					m_effects.push_back(Effect(pos[0], EFFECT::PLAYER_FIRE));
				});

			m_weapons[m_weaponNumber].setIsFired(false);
		}
	}

	//Second weapon
	//Double laser
	if (m_weaponNumber == 1)
	{
		glm::vec2 position[10];

		//First bullet position
		position[0] = m_position;
		position[0].y += m_texture.height;

		//Second bullet position
		position[1] = m_position;
		position[1].x += m_texture.width;  //Offset pos - bullet_texture
		position[1].y += m_texture.height;

		m_weapons[m_weaponNumber].update(m_input->isKeyDown(SDLK_SPACE), m_weapons[m_weaponNumber].getBulletsPerShoot(), position, glm::vec2(0.0f, 1.0f), *m_bullets, deltaTime);
	}

	//Update fire effects
	m_effects.erase(std::remove_if(m_effects.begin(),m_effects.end(),[deltaTime](Effect& e)
		{
			e.updateFireEffect(deltaTime);
			return e.getColorA() < e.getFadeSpeed();
		}),m_effects.end());
}

void Player::draw(Engine::SpriteBatch& spriteBatch)
{
	glm::vec4 posAndSize = glm::vec4(m_position.x, m_position.y, m_texture.width, m_texture.height);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	spriteBatch.draw(posAndSize, uv, m_texture.id, 0.0f, m_color);
}

bool Player::colideWithEnemy(Agent* agent)
{
	glm::vec2 enemyPosition = agent->getPosition();
	int enemyWidth = agent->getWidth();
	int enemyHeight = agent->getHeigh();

	if (m_position.x < enemyPosition.x + enemyWidth && m_position.x + m_texture.width > enemyPosition.x
		&& m_position.y < enemyPosition.y + enemyHeight && m_position.y + m_texture.height > enemyPosition.y)
	{
		return true;
	}

	return false;
}