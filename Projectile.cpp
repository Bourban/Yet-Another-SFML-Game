#include "Projectile.h"
#include "CharacterController.h"
#include "Character.h"
#include <SFML/Graphics/Texture.hpp>

Projectile::Projectile(double& elapsed, sf::Texture &tex, sf::Vector2f dir, OwnerTeam team, 
							float speed, float dam) : m_dir(dir), m_dam(dam), m_speed(speed), m_elapsed(elapsed), owner(team)
{
	this->setTexture(tex);

	m_rect.left = this->getPosition().x;
	m_rect.top = this->getPosition().y;
	m_rect.width = tex.getSize().x;
	m_rect.height = tex.getSize().y;
}

Projectile::Projectile(double& elapsed, sf::Texture &tex, sf::Vector2f dir, OwnerTeam team,
											float speed, float dam, sf::Vector2f scale) : m_dir(dir),
													m_dam(dam), m_speed(speed), m_elapsed(elapsed), owner(team)
{			
	this->setTexture(tex);
	this->setScale(scale);

	m_rect.left = this->getPosition().x;
	m_rect.top = this->getPosition().y;
	m_rect.width = tex.getSize().x * scale.x;
	m_rect.height = tex.getSize().y * scale.y;
}

Projectile::~Projectile()
{
}

OwnerTeam Projectile::getOwner() const
{
	return owner;
}

void Projectile::update()
{
	this->move((m_dir.x * m_speed) * m_elapsed, (m_dir.y * m_speed) * m_elapsed);
	handleBox();
}

void Projectile::draw(sf::RenderWindow & window)
{
	window.draw(*this);
}

void Projectile::checkCollision(Character &other)
{
	if(m_rect.intersects(other.getBody()))
	{
		//will probably break everything
		onHit(*(other.getController()));
	}
}

void Projectile::onHit(CharacterController &cc)
{
	cc.modifyHealth(-m_dam);
}

void Projectile::handleBox()
{
	m_rect.left = this->getPosition().x;
	m_rect.top = this->getPosition().y;
}
