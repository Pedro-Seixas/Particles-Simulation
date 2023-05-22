#include "SFML\Graphics.hpp"
#ifndef SPHERE_H
#define SPHERE_H

class Sphere
{
public:
	Sphere(sf::Vector2f position, float radius);

	float getRadius() const { return m_radius; }
	sf::Vector2f getPosition() const { return m_position; }

	void draw(sf::RenderWindow& window);
	void updatePosition(sf::RenderWindow& window);
	void setSphereStuckMouse(bool status);
	bool getSphereStuckMouse() const { return sphereStuckMouse; }

	sf::CircleShape getMSphere() const { return m_sphere; }

private:
	sf::CircleShape m_sphere;
	sf::Vector2f m_position;
	float m_radius;
	bool sphereStuckMouse = false;
};


#endif