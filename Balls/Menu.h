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
    bool getSphereStuckMouse() const { return sphereStuckMouse; }
    void setSphereStuckMouse(bool status);
    bool getSphereCreated() const { return sphereCreated; }
    //Sphere* sphere;
    std::vector<Sphere*> spheres;
    int getVectorSpheresSize() const { return spheres.size(); }

private:
    struct Button
    {
        sf::Texture buttonNormal;
        sf::Texture buttonSelected;
        sf::Sprite buttonSprite;
    };
    std::unique_ptr<Button[]> buttons;
    bool sphereStuckMouse = false;
    bool pressedOnce = true;
    bool sphereCreated = false;
};


#endif
