#include "Weapon.h"

Weapon::Weapon(std::string name, int fireRate, int bulletsPerShots, float bulletDamage, float bulletSpeed) :
	m_name(name),
	m_fireRate(fireRate),
	m_bulletsPerShoot(bulletsPerShots),
	m_bulletDamage(bulletDamage),
	m_bulletSpeed(bulletSpeed),
	m_frameCounter(0),
	m_lifeTime(50),
	m_isFired(false)
{}

void Weapon::update(bool isKeyPressed, int bulletsPerShots, const glm::vec2* position, const glm::vec2& direction, std::vector<Bullet>& bullets, float deltaTime)
{
	m_frameCounter += 1.0f * deltaTime;
	if (m_frameCounter >= m_fireRate && isKeyPressed)
	{
		for (int i = 0; i < bulletsPerShots; i++)
		{
			fire(position[i], direction, bullets);
		}
		m_isFired = true;
		m_frameCounter = 0;
	}
}

void Weapon::fire(const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets)
{
	bullets.emplace_back(position, direction, m_bulletSpeed, m_lifeTime, m_bulletDamage);
}