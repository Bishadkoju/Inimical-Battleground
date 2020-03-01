#include "Game.h"
Game::Game(int width, int height):window(sf::VideoMode(width, height), "Inimical BattleGrounds",sf::Style::Fullscreen)
//Game::Game(int width, int height) : window(sf::VideoMode(width, height), "Inimical BattleGrounds", sf::Style::Fullscreen)
{
	//window.setFramerateLimit(120);
	m_height = height;
	m_width=width;
	texture.loadFromFile("pic/army1.png");
	if (!texture.loadFromFile("pic/army1.png"))
	{

	}

	p.setArena(arena1);

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

void Game::handleKeyboardInput(sf::Keyboard::Key key, bool isPressed)
{
	
	if (key == sf::Keyboard::A) {
	//p.isPressedLeft = isPressed;
		userController.isPressedLeft = isPressed;
	
	}
	else if (key == sf::Keyboard::D) {
	//p.isPressedRight = isPressed;
		userController.isPressedRight = isPressed;
	}

	if (key == sf::Keyboard::W) {
	//p.isPressedUp = isPressed;
		userController.isPressedUp = isPressed;
	}
	
 
}

void Game::processEvents()
{

	//p.mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
	//p.isLeftMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	userController.mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
	userController.isLeftMouseButtonPressed= sf::Mouse::isButtonPressed(sf::Mouse::Left);
	userController.isRightMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);

	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handleKeyboardInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handleKeyboardInput(event.key.code, false);
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
	p.update(deltaTime,userController);
	//collision();
	
}

void Game::render()
{
	window.clear();
	arena1.draw(window);
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

