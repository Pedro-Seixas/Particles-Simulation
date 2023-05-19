#include "SFML\Graphics.hpp"
#ifndef SPHERE_H
#define SPHERE_H

class Sphere
{
public:
	Sphere(sf::Vector2f position, float radius, float mass);

	float getMass() const { return m_mass; }
	float getRadius() const { return m_radius; }

	void draw(sf::RenderWindow& window);
private:
	sf::CircleShape m_sphere;
	sf::Vector2f m_position;
	float m_radius;
	float m_mass;
};


#endif