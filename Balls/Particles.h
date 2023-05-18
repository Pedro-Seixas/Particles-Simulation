#include "SFML\Graphics.hpp"
#include <cmath>
#include <iostream>

#ifndef PARTICLES_H
#define PARTICLES_H

class Particles
{
public:
	Particles(sf::Color color, float radius, sf::Vector2f position);
	void draw(sf::RenderWindow& window);

	sf::Vector2f getPosition() const { return m_position; }
	sf::Vector2f getVelocity() const { return m_velocity; }

	void windowLimits(sf::RenderWindow& window);
	void updateVelocity(sf::Vector2f velocity);
	void updatePosition();
	void applyGravity();
	void orbitMouse(sf::Vector2i mousePosition);

private:
	sf::CircleShape m_particle;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	float m_gravity;

};

#endif