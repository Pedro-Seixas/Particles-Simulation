#ifndef MENU_H
#define MENU_H
#include "SFML/Graphics.hpp"
#include "Sphere.h"
#include <vector>
#include <iostream>

class Menu
{
public:
    Menu();
    void draw(sf::RenderWindow& window);
    void checkIfSelected(sf::RenderWindow& window);
    bool getSphereCreated() const { return sphereCreated; }
    std::vector<Sphere*> spheres;
    int getVectorSpheresSize() const { return spheres.size(); }
    void updatePosition(sf::RenderWindow& window, int id);

private:
    struct Button
    {
        sf::Texture buttonNormal;
        sf::Texture buttonSelected;
        sf::Sprite buttonSprite;
    };
    std::unique_ptr<Button[]> buttons;
    bool pressedOnce = true;
    bool sphereCreated = false;
};


#endif
