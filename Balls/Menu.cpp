#include "Menu.h"

Menu::Menu()
{
	buttons = std::make_unique<Button[]>(1);

	buttons[0].buttonNormal.loadFromFile("img/Sphere.png");
	buttons[0].buttonNormal.setSmooth(true);

	buttons[0].buttonSelected.loadFromFile("img/SphereSelected.png");
	buttons[0].buttonSelected.setSmooth(true);

	buttons[0].buttonSprite.setTexture(buttons[0].buttonNormal);
	buttons[0].buttonSprite.setPosition(sf::Vector2f(20.f, 20.f));
}

void Menu::draw(sf::RenderWindow& window)
{
	checkIfSelected(window);
	window.draw(buttons[0].buttonSprite);

	if (sphereCreated)
	{
		if (sphereStuckMouse)
		{
			sphere->updatePosition(window);
		}

		sphere->draw(window);
	}
}

void Menu::checkIfSelected(sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos);

    if (buttons[0].buttonSprite.getGlobalBounds().contains(mousePosView)) 
	{

        buttons[0].buttonSprite.setTexture(buttons[0].buttonSelected);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && pressedOnce)
		{
			sphere = new Sphere(mousePosView, 50.f, 5000.f);
			sphereStuckMouse = true;
			pressedOnce = false;
			sphereCreated = true;
		}

		
    }
    else
    {
        buttons[0].buttonSprite.setTexture(buttons[0].buttonNormal);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sphereStuckMouse = false;
			pressedOnce = true;
		}
    }

}

void Menu::setSphereStuckMouse(bool status)
{
	sphereStuckMouse = status;
}