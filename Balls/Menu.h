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
    void draw(sf::RenderWindow& window, sf::Event& event);
    void checkIfSelected(sf::RenderWindow& window, sf::Event& event);
    bool getSphereCreated() const { return sphereCreated; }
    std::vector<Sphere*> spheres;
    int getVectorSpheresSize() const { return spheres.size(); }
    void updatePosition(sf::RenderWindow& window, int id);
    void changeButtonImage(int buttonId);
    bool getResetStatus() const { return resetStatus; }
    bool getMouseStatus() const { return mouseStatus; }
    void changeNumberOfParticles(std::string text);

private:
    struct Button
    {
        sf::Texture buttonNormal;
        sf::Texture buttonSelected;
        sf::Sprite buttonSprite;
        sf::Texture buttonTypeTwoNormal;
        sf::Texture buttonTypeTwoSelected;
        int type = 1;
    };
    std::unique_ptr<Button[]> buttons;

    bool pressedOnce = true;
    bool sphereCreated = false;
    bool pressedButtonOnce = false;
    bool resetStatus = true;
    bool mouseStatus = true;

    //Text
    sf::Text m_text;
    sf::Font font;
    sf::Vector2f m_textPosition;
};


#endif
