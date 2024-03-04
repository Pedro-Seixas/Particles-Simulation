#include <SFML/Graphics.hpp>
#include "Particles.h"
#include "Sphere.h"
#include "Menu.h"
#include <SFML/OpenGL.hpp>


enum windowState { spheres, imageToParticle };

int main()
{
    windowState currentState = imageToParticle;
    int numberOfParticles = 40 * 40;

    sf::Color color(255, 255, 255);
    std::vector<Particles> particles;
    sf::Vector2f position = sf::Vector2f(300.f, 300.f);
    sf::Vector2f position2 = sf::Vector2f(500, 200);

    //Image Processing
    sf::Image img;

    if (!img.loadFromFile("imgUploaded/shrek.jpg"))
    {
        std::cout << "Failed to Load Image" << std::endl;
    }

    //Resize image so the computer doesnt go boom when creating particles
    sf::Texture texture;
    texture.loadFromImage(img);

    sf::Image originalImage = texture.copyToImage();
    sf::Vector2u originalSize = originalImage.getSize();

    int imageHeight = sqrt(numberOfParticles);
    int imageWidth = sqrt(numberOfParticles);

    sf::Image resizedImage;
    resizedImage.create(imageHeight, imageWidth);

    sf::Vector2f scaleFactors(static_cast<float>(originalSize.x) / imageWidth, static_cast<float>(originalSize.y) / imageHeight);
    for (unsigned int x = 0; x < imageWidth; x++) {
        for (unsigned int y = 0; y < imageHeight; y++) {
            sf::Color color = originalImage.getPixel(x * scaleFactors.x, y * scaleFactors.y);
            resizedImage.setPixel(x, y, color);

        }
    }

    for (int x = 0; x < imageHeight; x++)
    {
        for (int y = 0; y < imageWidth; y++)
        {
            color = resizedImage.getPixel(y, x);
            position2 = sf::Vector2f(position2.x + 2, position2.y);
            Particles particle(color, 1, position2);
            particles.push_back(particle);
        }
        position2.y = position2.y + 2;
        position2.x = 500;
    }

    //END IMAGE PROCESSING
    //Create all particles
    //int count = 0;
    //for (int i = 0; i < numberOfParticles; ++i) {
    //    sf::Color color(count, 255, 255);
    //    position = sf::Vector2f(position.x + 0.1, position.y);
    //    Particles particle(color, 2, position);
    //    particles.push_back(particle);

    //    if (count == 253) {
    //        count = 0;
    //    }
    //    count++;
    //}

    Menu menu;

    std::string particleText = std::to_string(numberOfParticles) + " Particles";
    menu.changeNumberOfParticles(particleText);

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
        switch (currentState)
        {
        case spheres:

            window.clear();

            //Toggle between escape/orbit mouse
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && menu.getMouseStatus())
            {
                for (int i = 0; i < numberOfParticles; i++)
                {
                    particles[i].escapeMouse(sf::Mouse::getPosition(window));
                }
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !menu.getMouseStatus())
            {
                for (int i = 0; i < numberOfParticles; i++)
                {
                    particles[i].orbitMouse(sf::Mouse::getPosition(window));
                }
            }
            //Toggle between Reset ON or Reset OFF
            if (menu.getResetStatus())
            {
                for (int i = 0; i < numberOfParticles; i++)
                {
                    particles[i].resetForce(window);
                }
            }
            //Check if there are spheres created before calling them
            if (menu.getSphereCreated())
            {
                for (int i = 0; i < numberOfParticles; i++)
                {
                    for (int j = 0; j < menu.getVectorSpheresSize(); j++)
                    {
                        if (!menu.spheres[j]->getSphereStuckMouse())
                        {
                            particles[i].orbitSphere(menu.spheres[j]->getPosition(), menu.spheres[j]->getRadius());
                        }
                    }
                }

            }

            //Draw Particles
            for (int i = 0; i < numberOfParticles; i++)
            {
                particles[i].draw(window);
            }

            menu.draw(window, event);
            window.display();

            break;

        case imageToParticle:

            window.clear();

            //Toggle between escape/orbit mouse
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && menu.getMouseStatus())
            {
                for (int i = 0; i < numberOfParticles; i++)
                {
                    particles[i].escapeMouse(sf::Mouse::getPosition(window));
                }
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !menu.getMouseStatus())
            {
                for (int i = 0; i < numberOfParticles; i++)
                {
                    particles[i].orbitMouse(sf::Mouse::getPosition(window));
                }
            }
            //Toggle between Reset ON or Reset OFF
            if (menu.getResetStatus())
            {
                for (int i = 0; i < numberOfParticles; i++)
                {
                    particles[i].resetForce(window);
                }
            }

            for (int i = 0; i < numberOfParticles; ++i) {
                particles[i].draw(window/*, shader*/);
            }

            menu.draw(window, event);
            window.display();
        }
        
    }

    return 0;
}