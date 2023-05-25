#include "Menu.h"

Menu::Menu()
{
	buttons = std::make_unique<Button[]>(3);

	//Sphere Button
	buttons[0].buttonNormal.loadFromFile("img/Sphere.png");
	buttons[0].buttonNormal.setSmooth(true);

	buttons[0].buttonSelected.loadFromFile("img/SphereSelected.png");
	buttons[0].buttonSelected.setSmooth(true);

	buttons[0].buttonSprite.setTexture(buttons[0].buttonNormal);
	buttons[0].buttonSprite.setPosition(sf::Vector2f(20.f, 20.f));

	//Orbit/Escape Mouse Button
	buttons[1].buttonNormal.loadFromFile("img/EscapeMouseNormal.png");
	buttons[1].buttonNormal.setSmooth(true);
	buttons[1].buttonTypeTwoNormal.loadFromFile("img/OrbitMouseNormal.png");
	buttons[1].buttonTypeTwoNormal.setSmooth(true);

	buttons[1].buttonSelected.loadFromFile("img/EscapeMouseSelected.png");
	buttons[1].buttonSelected.setSmooth(true);
	buttons[1].buttonTypeTwoSelected.loadFromFile("img/OrbitMouseSelected.png");
	buttons[1].buttonTypeTwoSelected.setSmooth(true);

	buttons[1].buttonSprite.setTexture(buttons[1].buttonNormal);
	buttons[1].buttonSprite.setPosition(sf::Vector2f(100.f, 20.f));
	buttons[1].buttonSprite.setScale(0.5,0.5);
	//Reset Button
	buttons[2].buttonNormal.loadFromFile("img/ResetONNormal.png");
	buttons[2].buttonNormal.setSmooth(true);
	buttons[2].buttonTypeTwoNormal.loadFromFile("img/ResetOFFNormal.png");
	buttons[2].buttonTypeTwoNormal.setSmooth(true);

	buttons[2].buttonSelected.loadFromFile("img/ResetONSelected.png");
	buttons[2].buttonSelected.setSmooth(true);
	buttons[2].buttonTypeTwoSelected.loadFromFile("img/ResetOFFSelected.png");
	buttons[2].buttonTypeTwoSelected.setSmooth(true);

	buttons[2].buttonSprite.setTexture(buttons[2].buttonNormal);
	buttons[2].buttonSprite.setPosition(sf::Vector2f(220.f, 20.f));
	buttons[2].buttonSprite.setScale(0.5, 0.5);

	//Text
	if (!font.loadFromFile("fonts/OpenSans-SemiBold.ttf"))
	{
		std::cout << "Failed to load Font" << std::endl;
	}

	m_text.setString("0 Particles");
	m_text.setFont(font);
	m_text.setCharacterSize(32);
	m_text.setFillColor(sf::Color::White);
	m_text.setPosition(sf::Vector2f(600.f, 20.f));
}

void Menu::draw(sf::RenderWindow& window, sf::Event& event)
{
	updatePosition(window, 1);
	checkIfSelected(window, event);

	for (int i = 0; i < 3; i++)
	{

		window.draw(buttons[i].buttonSprite);
	}

	window.draw(m_text);
}

void Menu::checkIfSelected(sf::RenderWindow& window, sf::Event& event)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos);

	for (int i = 0; i < 3; i++)
	{
		//Change Button Images To Selected
		if (buttons[i].buttonSprite.getGlobalBounds().contains(mousePosView))
		{
			if (buttons[i].type == 1 && i != 0)
			{
				buttons[i].buttonSprite.setTexture(buttons[i].buttonSelected);
			}
			else if (buttons[i].type == 2)
			{
				buttons[i].buttonSprite.setTexture(buttons[i].buttonTypeTwoSelected);
			}
			else if (i == 0)
			{
				buttons[i].buttonSprite.setTexture(buttons[i].buttonSelected);
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (pressedOnce && i == 0)
				{
					Sphere* sphere = new Sphere(mousePosView, 50.f);
					spheres.push_back(sphere);

					spheres[spheres.size() - 1]->setSphereStuckMouse(true);
					pressedOnce = false;
					sphereCreated = true;
				}
				else if (i != 0 && !pressedButtonOnce)
				{
					pressedButtonOnce = true;
					changeButtonImage(i);
				}

			}
			else
			{
				pressedOnce = true;
				pressedButtonOnce = false;
			}
		}
		else
		{
			if (buttons[i].type == 1 && i != 0)
			{
				buttons[i].buttonSprite.setTexture(buttons[i].buttonNormal);
			}
			else if (buttons[i].type == 2)
			{
				buttons[i].buttonSprite.setTexture(buttons[i].buttonTypeTwoNormal);
			}
			else if (i == 0)
			{
				buttons[i].buttonSprite.setTexture(buttons[i].buttonNormal);
			}
		}

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

void Menu::changeButtonImage(int buttonId)
{
	if (buttonId == 1)
	{
		//Type 1 = Reset ON or Escape Mouse
		//Type 2 = Reset OFF or Orbit Mouse
		if (buttons[buttonId].type == 1)
		{
			buttons[buttonId].buttonSprite.setTexture(buttons[buttonId].buttonTypeTwoNormal);
			buttons[buttonId].type = 2;
			mouseStatus = false;
		}
		else if (buttons[buttonId].type == 2)
		{
			buttons[buttonId].buttonSprite.setTexture(buttons[buttonId].buttonNormal);
			buttons[buttonId].type = 1;
			mouseStatus = true;
		}
	}
	else if (buttonId == 2)
	{
		if (buttons[buttonId].type == 1)
		{
			buttons[buttonId].buttonSprite.setTexture(buttons[buttonId].buttonTypeTwoNormal);
			buttons[buttonId].type = 2;
			resetStatus = false;
		}
		else if (buttons[buttonId].type == 2)
		{
			buttons[buttonId].buttonSprite.setTexture(buttons[buttonId].buttonNormal);
			buttons[buttonId].type = 1;
			resetStatus = true;
		}
	}
}

void Menu::changeNumberOfParticles(std::string text)
{
	m_text.setString(text);
}