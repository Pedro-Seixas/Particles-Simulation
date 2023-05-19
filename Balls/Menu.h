#ifndef MENU_H
#define MENU_H
#include "SFML/Graphics.hpp"
#include "Sphere.h"

class Menu
{
public:
    Menu();
    void draw(sf::RenderWindow& window);
    void checkIfSelected(sf::RenderWindow& window);
    bool getSphereStuckMouse() const { return sphereStuckMouse; }
    void setSphereStuckMouse(bool status);

private:
    struct Button
    {
        sf::Texture buttonNormal;
        sf::Texture buttonSelected;
        sf::Sprite buttonSprite;
    };
    Sphere* sphere;
    std::unique_ptr<Button[]> buttons;
    bool sphereStuckMouse = false;
    bool pressedOnce = true;
    bool sphereCreated = false;
};


#endif
