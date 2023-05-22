#include <SFML/Graphics.hpp>
#include "Particles.h"
#include "Sphere.h"
#include "Menu.h"

int main()
{
    int numberOfParticles = 2000;
    sf::Color color(255, 255, 255);

    std::vector<Particles> particles;
    sf::Vector2f position = sf::Vector2f(300.f, 300.f);

    Menu menu;


    for (int i = 0; i < numberOfParticles; ++i) {
        position = sf::Vector2f(position.x + 0.2, position.y + 0.1);
        Particles particle(color, 1, position);
        particles.push_back(particle);
    }

    sf::RenderWindow window(sf::VideoMode(1480, 720), "Particles");
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

        if (menu.getSphereCreated())
        {
            for (int i = 0; i < numberOfParticles; i++)
            {
                for (int j = 0; j < menu.getVectorSpheresSize()-1; j++)
                {
                    if (!menu.spheres[j]->getSphereStuckMouse())
                    {
                        particles[i].orbitSphere(menu.spheres[j]->getPosition(), menu.spheres[j]->getRadius());
                    }
                }
            }
            
        }

        window.clear();
        for (int i = 0; i < numberOfParticles; i++)
        {
            particles[i].draw(window);
        }
        menu.draw(window);
        window.display();
    }

    return 0;
}