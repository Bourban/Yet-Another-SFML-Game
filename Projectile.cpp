#include "Projectile.h"
#include "CharacterController.h"
#include "Character.h"
#include "Helpers.h"
#include <SFML/Graphics/Texture.hpp>

Projectile::Projectile(double& elapsed, sf::Texture &tex, sf::Vector2f dir, sf::Vector2f pos, OwnerTeam team,
											float speed, float dam, sf::Vector2f scale) : m_dir(dir),
													m_dam(dam), m_speed(speed), m_elapsed(elapsed), owner(team)
{			
	this->setTexture(tex);
	this->setOrigin(tex.getSize().x / 2, tex.getSize().y / 2);
	this->setScale(scale);
	this->setPosition(pos);

	m_spriteSize = sf::Vector2f(tex.getSize().x * scale.x, tex.getSize().y * scale.y);

	m_rect.left = this->getPosition().x - m_spriteSize.x / 2;
	m_rect.top = this->getPosition().y - m_spriteSize.y / 2;
	m_rect.width = m_spriteSize.x;
	m_rect.height = m_spriteSize.y;

	pls.setSize(m_spriteSize);
	pls.setOutlineColor(sf::Color::Black);
	pls.setOutlineThickness(1.0f);
	pls.setFillColor(sf::Color::Transparent);
	//pls.setOrigin(m_spriteSize / 2.0f);
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
	if (Helpers::bDebugMode == true)
	window.draw(pls);
}

bool Projectile::checkCollision(Character &other)
{
	if(m_rect.intersects(other.getBody()))
	{
		//will probably break everything
		onHit(*(other.getController()));
		return true;
	}

	return false;
}

void Projectile::onHit(CharacterController &cc)
{
	cc.modifyHealth(-m_dam);
}

void Projectile::handleBox()
{
	m_rect.left = this->getPosition().x - m_spriteSize.x / 2;
	m_rect.top = this->getPosition().y - m_spriteSize.y / 2;

	pls.setPosition(m_rect.left, m_rect.top);
}
