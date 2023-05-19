#include <SFML/Graphics.hpp>
#include "Particles.h"
#include "Sphere.h"

int main()
{
    int numberOfParticles = 200;
    sf::Color color(255, 255, 255);

    std::vector<Particles> particles;
    sf::Vector2f position = sf::Vector2f(300.f, 300.f);

    //Sphere sphere(sf::Vector2f(500.f, 300.f), 50.f, 5000.f);


    for (int i = 0; i < numberOfParticles; ++i) {
        position = sf::Vector2f(position.x + 0.2, position.y);
        Particles particle(color, 0.5, position);
        particles.push_back(particle);
    }

    sf::RenderWindow window(sf::VideoMode(1480, 720), "SFML works!");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            for (int i = 0; i < numberOfParticles; i++)
            {
                particles[i].orbitMouse(sf::Mouse::getPosition(window));
            }
        }

        window.clear();
        for (int i = 0; i < numberOfParticles; i++)
        {
            particles[i].draw(window);
        }
        sphere.draw(window);
        window.display();
    }

    return 0;
}