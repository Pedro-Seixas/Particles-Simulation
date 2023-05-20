#include "Sphere.h"
#include <iostream>

Sphere::Sphere(sf::Vector2f position, float radius)
{
	m_position = position;
	m_sphere.setPosition(position);

	m_radius = radius;
	m_sphere.setRadius(radius);


	std::cout << "Sphere Created" << std::endl;
}

void Sphere::draw(sf::RenderWindow& window)
{
	window.draw(m_sphere);
}

void Sphere::updatePosition(sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos);

	m_position = mousePosView - sf::Vector2f(m_radius, m_radius);
	m_sphere.setPosition(m_position);

}