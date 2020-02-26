#include "Game.h"
Game::Game(int width, int height):window(sf::VideoMode(width, height), "Inimical BattleGrounds")
//Game::Game(int width, int height) : window(sf::VideoMode(width, height), "Inimical BattleGrounds", sf::Style::Fullscreen)
{
	m_height = height;
	m_width=width;
	texture.loadFromFile("pic/army1.png");
	if (!texture.loadFromFile("pic/army1.png"))
	{

	}


}
	

void Game::run()
{
	sf::Clock clock;
	
	
	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		processEvents();
		update(deltaTime);
		render();
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	
	if (key == sf::Keyboard::A) {
		//p.setXVelocity(-1, isPressed);
		p.isPressedLeft = isPressed;
		//std::cout << "A " << isPressed << std::endl;
	}
	else if (key == sf::Keyboard::D) {
		//p.setXVelocity(1, isPressed);
		p.isPressedRight = isPressed;
		//std::cout << "D " << isPressed << std::endl;
	}
	if (key == sf::Keyboard::W) {
		p.isPressedUp = isPressed;
	}
 
}

void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
			
		
	}
}

void Game::update(sf::Time deltaTime)
{
	p.update(deltaTime);
	//collision();
	
}

void Game::render()
{
	window.clear();
	p.draw(window);
	
	
	sf::Sprite sprite(texture);
	sprite.setPosition(p.getCoordinate().x, p.getCoordinate().y);
	//window.draw(sprite);
	
	window.display();
	
}

void Game::collision()
{
	
	if (p.getCoordinate().y >= 700 ) {
		p.isCollided = true;
		
		p.setCoordinate(p.getCoordinate().x, 700);
	}
	else {
		p.isCollided = false;
	}

}

