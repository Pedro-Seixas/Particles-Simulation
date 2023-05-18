#include "Particles.h"

Particles::Particles(sf::Color color, float radius, sf::Vector2f position) : m_gravity(2), m_velocity(0.f, 0.f)
{
    m_particle.setFillColor(color);

    m_particle.setRadius(radius);

    m_position = position;
    m_particle.setPosition(position);

    updateVelocity(sf::Vector2f(0, m_gravity));
}


void Particles::draw(sf::RenderWindow& window)
{
    //windowLimits(window);

    applyGravity();

    window.draw(m_particle);
}

void Particles::windowLimits(sf::RenderWindow& window)
{
    if (m_position.x >= window.getSize().x || m_position.x < 0)
    {
        m_velocity.x = -m_velocity.x;
    }
    if (m_position.y >= window.getSize().y || m_position.y < 0)
    {
        m_velocity.y = -m_velocity.y;
    }
}

void Particles::updateVelocity(sf::Vector2f velocity)
{
    m_velocity = velocity;
}

void Particles::updatePosition()
{
    m_particle.setPosition(m_position);
}

void Particles::applyGravity()
{
    m_position = sf::Vector2f(m_position.x + m_velocity.x, m_position.y + m_velocity.y);
    updatePosition();
}

void Particles::orbitMouse(sf::Vector2i mousePosition)
{
    //Inverse Squre Law
    //Intensity = 1/distance^2
    float distance_x = m_position.x - mousePosition.x;
    float distance_y = m_position.y - mousePosition.y;

    float distance = sqrt(pow(distance_x, 2) + pow(distance_y, 2));

    float distanceLimit = 50;

    float intensity = 10 / pow(distance, 2);

    sf::Vector2f acceleration = sf::Vector2f(-distance_x * intensity, -distance_y * intensity);

    m_velocity = sf::Vector2f(m_velocity.x + acceleration.x, m_velocity.y + acceleration.y);

    if (distance < distanceLimit)
    {
        m_velocity = sf::Vector2f(0, 0);
    }
}