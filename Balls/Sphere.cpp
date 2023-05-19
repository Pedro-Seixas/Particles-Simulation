#include "Sphere.h"

Sphere::Sphere(sf::Vector2f position, float radius, float mass)
{
	m_position = position;
	m_sphere.setPosition(position);

	m_radius = radius;
	m_sphere.setRadius(radius);

	m_mass = mass;
	
}

void Sphere::draw(sf::RenderWindow& window)
{
	window.draw(m_sphere);
}