#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <glm/glm.hpp>
#include <vector>

#include "Bullet.h"

class Weapon
{
public:
	Weapon(std::string name, int fireRate, int bulletsPerShots, float bulletDamage, float bulletSpeed);
	~Weapon();

	void update(bool isKeyPressed, int bulletsPerShots, const glm::vec2* position, const glm::vec2& direction, std::vector<Bullet>& bullets, float deltaTime);

	//Getters
	bool getIsFired() { return  this->m_isFired; }
	int getBulletsPerShoot() { return this->m_bulletsPerShoot; }

	//Setters
	void setIsFired(bool isFired) { m_isFired = isFired; }

private:
	void fire(const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets);

	std::string m_name;

	int m_fireRate;
	int m_bulletsPerShoot;
	int m_bulletDamage;

	float m_bulletSpeed;
	float m_frameCounter;
	float m_lifeTime;

	bool m_isFired;
};

#endif  //WEAPON_H