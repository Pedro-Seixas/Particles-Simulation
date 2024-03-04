#include "Particles.h"

Particles::Particles(sf::Color color, float radius, sf::Vector2f position) : m_gravity(0), m_velocity(0.f, 0.f)
{
    m_particle.setFillColor(color);

    m_particle.setRadius(radius);

    m_position = position;
    m_particle.setPosition(position);
    m_startPosition = m_position;
    updateVelocity(sf::Vector2f(0, m_gravity));
}


void Particles::draw(sf::RenderWindow& window/*, sf::Shader& shader*/)
{
    //windowLimits(window);
    applyForces();

    window.draw(m_particle/*, &shader*/);
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

void Particles::applyForces()
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

    float distance = pow(distance_x, 2) + pow(distance_y, 2);

    float distanceLimit = 50;

    float intensity = 10 / distance;

    if (distance < distanceLimit)
    {
        intensity = 0;
    }

    sf::Vector2f acceleration = sf::Vector2f(-distance_x * intensity, -distance_y * intensity);

    m_velocity = sf::Vector2f(m_velocity.x + acceleration.x, m_velocity.y + acceleration.y);

}

void Particles::orbitSphere(sf::Vector2f spherePosition, float radius)
{

    float distance_x = m_position.x - spherePosition.x - radius;
    float distance_y = m_position.y - spherePosition.y - radius;

    float distance =pow(distance_x, 2) + pow(distance_y, 2);

    float distanceLimit = 50;

    float intensity = 10 / distance;

    sf::Vector2f acceleration = sf::Vector2f(-distance_x * intensity, -distance_y * intensity);

    m_velocity = sf::Vector2f(m_velocity.x + acceleration.x, m_velocity.y + acceleration.y);

    if (distance< distanceLimit)
    {
        m_velocity = sf::Vector2f(0, 0);
    }

}

//Function Responsible For Making the Particles Return To Initial Position
void Particles::resetForce(sf::RenderWindow& window)
{
    float distance_x = m_startPosition.x - m_position.x;
    float distance_y = m_startPosition.y - m_position.y;

    float distance = sqrt(pow(distance_x, 2) + pow(distance_y, 2));

    float intensity = 0.05;

    float limitDistance = 500;

    //Higher Distance, Higher Acceleration
    sf::Vector2f acceleration = sf::Vector2f(distance_x * intensity, distance_y * intensity);

    if (distance < 0.2 && std::abs(m_velocity.x) < 0.1 && std::abs(m_velocity.y) < 0.1)
    {
        m_velocity = sf::Vector2f(0, 0);
    }
    else
    {
        m_velocity += acceleration;
    }

    //This makes sure the particles do not resonate and stop moving after finding its spot.
    if (distance < limitDistance)
    {
        m_velocity = m_velocity / (float)1.5;
    }

}

void Particles::escapeMouse(sf::Vector2i mousePosition)
{
    float distance_x = m_position.x - mousePosition.x;
    float distance_y = m_position.y - mousePosition.y;

    float distance = pow(distance_x, 2) + pow(distance_y, 2);

    float distanceLimit = 1;

    float intensity = 100 / distance;

    //This is necessary so particles do not go very far away very quickly (inverse square law)
    //Intensity tend to infinite when the distance tend to 0.
    if (distance < distanceLimit)
    {
        intensity = 0;
    }

    sf::Vector2f acceleration = sf::Vector2f(distance_x * intensity, distance_y * intensity);

    m_velocity = sf::Vector2f(m_velocity.x + acceleration.x, m_velocity.y + acceleration.y);

}
