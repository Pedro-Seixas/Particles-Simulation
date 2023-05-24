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
	updatePosition(window, 1);
	checkIfSelected(window);

	window.draw(buttons[0].buttonSprite);
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
			Sphere* sphere = new Sphere(mousePosView, 50.f);
			spheres.push_back(sphere);

			spheres[spheres.size()-1]->setSphereStuckMouse(true);
			pressedOnce = false;
			sphereCreated = true;
		}


	}
	else
	{
		buttons[0].buttonSprite.setTexture(buttons[0].buttonNormal);
	}
	

	for (int i = 0; i < spheres.size(); i++)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && spheres[i]->getMSphere().getGlobalBounds().contains(mousePosView))
		{
			spheres[i]->setSphereStuckMouse(true);

			break;
		}
		else if (sf::Event::MouseButtonReleased && spheres[i]->getMSphere().getGlobalBounds().contains(mousePosView))
		{
			spheres[i]->setSphereStuckMouse(false);

			pressedOnce = true;

			break;
		}

	}

}


void Menu::updatePosition(sf::RenderWindow& window, int id)
{
	for (int i = 0; i < spheres.size(); i++)
	{
		if (sphereCreated)
		{
			if (spheres[i]->getSphereStuckMouse())
			{
				spheres[i]->updatePosition(window);
			}
			for (int i = 0; i < spheres.size(); i++)
			{
				spheres[i]->draw(window);
			}
		}
	}
}