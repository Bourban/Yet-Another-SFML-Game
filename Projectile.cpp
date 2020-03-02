#include "Projectile.h"
#include "CharacterController.h"


Projectile::Projectile(double& elapsed, sf::Texture & tex, sf::Vector2f dir, float speed, float dam, OwnerTeam team) : m_dir(dir), m_dam(dam), m_speed(speed), m_elapsed(elapsed), owner(team)
{
	this->setTexture(tex);
}

Projectile::Projectile(double& elapsed, sf::Texture & tex, sf::Vector2f scale, sf::Vector2f dir, float speed, float dam, OwnerTeam team) : m_dir(dir), m_dam(dam), m_speed(speed), m_elapsed(elapsed),
																																				owner(team)
{
	this->setTexture(tex);
	this->setScale(scale);
}

Projectile::Projectile(double& elapsed, sf::Texture & tex, sf::Vector2f dir, float speed) : m_dir(dir), m_speed(speed), m_elapsed(elapsed)
{
	this->setTexture(tex);
}

Projectile::Projectile(double & elapsed, sf::Texture & tex, sf::Vector2f dir) : m_dir(dir), m_elapsed(elapsed)
{
	this->setTexture(tex);
}

Projectile::~Projectile()
{
}

void Projectile::update()
{
	this->move((m_dir.x * m_speed) * m_elapsed, (m_dir.y * m_speed) * m_elapsed);
}

void Projectile::draw(sf::RenderWindow & window)
{
	window.draw(*this);
}

void Projectile::onHit(CharacterController & cc)
{
	cc.modifyHealth(-m_dam);
}
