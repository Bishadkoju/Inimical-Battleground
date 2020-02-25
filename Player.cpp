#include "Player.h"

Player::Player()
{
	isPressedLeft = false;
	isPressedRight = false;
	isPressedUp = false;
	isCollided = false;
	isOnGround = false;

	coordinate.x = 200;
	coordinate.y = 200;
	currentVelocity.x = 0;
	currentVelocity.y = 0;
	targetVelocity.x = 0;
	targetVelocity.y = 0;
	maxGroundVelocity.x =30;
	maxAirVelocity.x = 60;
	maxAirVelocity.y = 80;
	thrustValue = 9000;

	texture.loadFromFile("pic/army1.png");

	body.setSize(sf::Vector2f(10.f, 10.f));
	//body.setRotation(60.f);

	groundDampingConstant = 100;
	airDampingConstant = 50;
	gravity = 50;
	elasticConstant = 0.3;


	noKeyWasPressed = true;
	//directions
	facingRight = true;
	facingLeft = false;
	//animations spritesheet
	animations[int(AnimationIndex::flyingright)] = Animation(0, 152, 95, 150, "right");
	animations[int(AnimationIndex::flyingleft)] = Animation(0, 152, 95, 150, "left");
	animations[int(AnimationIndex::walkingright)] = Animation(0, 0, 95, 150, "right");
	animations[int(AnimationIndex::walkingleft)] = Animation(0, 0, 95, 150, "left");
	//animations[int(AnimationIndex::standing)] = Animation(0, 0, 95, 150, "left", noKeyWasPressed);
	lhand.loadFromFile("pic/lhand.png");
	rhand.loadFromFile("pic/rhand.png");
	playerHandLeft.setTexture(lhand);
	playerHandRight.setTexture(rhand);
	/*spritePlayer.setScale(0.5, 0.5);
	playerHandLeft.setScale(0.5, 0.5);
	playerHandRight.setScale(0.5,0.5);*/

}



void Player::update(sf::Time deltaTime)
{
	isOnGround = currentVelocity.y == 0;
	noKeyWasPressed = !(isPressedLeft || isPressedRight || isPressedUp);
	//std::cout << isCollided << std::endl;
	this->deltaTime = deltaTime;
	if (isPressedLeft) {
		targetVelocity.x = -maxAirVelocity.x;
		//curAnimation = AnimationIndex::walkingleft;
		facingLeft = true;
		facingRight = false;
	}
	else if (isPressedRight) {
		targetVelocity.x = maxAirVelocity.x;
		//curAnimation = AnimationIndex::walkingright;
		facingRight = true;
		facingLeft = false;
	}
	else {
		targetVelocity.x = 0;
	}

	if (isPressedUp) {
		
		targetVelocity.y -= deltaTime.asSeconds() * gravity*2;
	
	}
	else {
		//targetVelocity.y = currentVelocity.y;
	}
	
	/*if (!(isPressedUp || isPressedRight || isPressedLeft))
	{
		curAnimation = AnimationIndex::standing;
	}*/
	



	targetVelocity.y += deltaTime.asSeconds() * gravity;
	
	currentVelocity.x = interpolateVelocity(targetVelocity.x, currentVelocity.x, airDampingConstant);
	
	currentVelocity.y = interpolateVelocity(targetVelocity.y, currentVelocity.y, airDampingConstant);
	std::cout << currentVelocity.y << std::endl;
	
	coordinate.x += currentVelocity.x *5*deltaTime.asSeconds();
	coordinate.y += currentVelocity.y * 5 * deltaTime.asSeconds();

	body.setPosition(coordinate);

	isCollided = getCollider().checkCollision(Collider(bar));

	if (isCollided && currentVelocity.y > 0) {
		if (abs(currentVelocity.y) < 1) { currentVelocity.y = 0; }
		currentVelocity.y =-elasticConstant*currentVelocity.y;
		targetVelocity.y = 0; 
		
	}
	if (isCollided && currentVelocity.x > 0) {
		//if (currentVelocity.y < 1) { currentVelocity.y = 0; }
		currentVelocity.x = -0.21 * currentVelocity.x;
		//targetVelocity.y = 0;

	}
		
	
}
void Player::setCoordinate(sf::Vector2f coordinate)
{
	this->coordinate = coordinate;
}
void Player::setCoordinate(float x, float y)
{
	sf::Vector2f temp;
	temp.x = x;
	temp.y = y;
	this->coordinate = temp;
}
void Player::setXVelocity(int direction,bool isPressed)
{
	this->targetVelocity.x = isPressed?maxGroundVelocity.x*direction:0.f;
}
void Player::getUserInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		currentVelocity.x = -maxGroundVelocity.x;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		currentVelocity.x = maxGroundVelocity.x;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		currentVelocity.y = -maxGroundVelocity.y;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		currentVelocity.y = +maxGroundVelocity.y;
	}
}

Collider Player::getCollider()
{
	 return Collider(body); 
}



sf::Vector2f Player::getCoordinate()
{
	return this->coordinate;
}

sf::Vector2f Player::getVelocity()
{
	return this->currentVelocity;
}

float Player::interpolateVelocity(float target, float current, float dampingFactor)
{
	float increment = dampingFactor * this->deltaTime.asSeconds();
	float difference = target - current;
	if (difference >increment) {
		return current + increment;
	}
	if (difference < -increment) {
		return current - increment;
	}
	return target;

}

void Player::draw(sf::RenderWindow& window)
{
	if (facingLeft) {
		curAnimation = AnimationIndex::walkingleft;
	}
	if (facingRight) {
		curAnimation = AnimationIndex::walkingright;
	}
	if (!isOnGround) {
		if (isPressedLeft ||(isPressedUp && facingLeft)) {
			curAnimation = AnimationIndex::flyingleft;
		}
		if (isPressedRight ||(isPressedUp && facingRight)) {
			curAnimation = AnimationIndex::flyingright;
		}
	}

	if (!(noKeyWasPressed)) {
		animations[int(curAnimation)].update(deltaTime);
	}
	animations[int(curAnimation)].applySprite(spritePlayer);
	body.setFillColor(sf::Color(100, 250, 50));
	//body.setFillColor(sf::Color::Transparent);
	//body.setTexture(&texture,false);
	body.setSize(sf::Vector2f(100, 150));
	window.draw(body);
	bar.setSize(sf::Vector2f(500, 50));
	bar.setFillColor(sf::Color(100, 250, 50));
	bar.setPosition(800, 500);
	window.draw(bar);
	setBulletDir(window);
	window.draw(spritePlayer);
	if (facingLeft)
	{
		playerHandLeft.setPosition(getCoordinate().x - 40, getCoordinate().y + 60);
		window.draw(playerHandLeft);
	}
	if (!facingLeft)
	{
		playerHandRight.setPosition(getCoordinate().x + 20, getCoordinate().y + 60);
		window.draw(playerHandRight);
	}


	spritePlayer.setPosition(getCoordinate().x, getCoordinate().y);
	


}


void Player::setBulletDir(sf::RenderWindow& window)
{
	playerCenter = sf::Vector2f(getCoordinate());

	//playerHandRight.setPosition(getCoordinate().x + 10.f, getCoordinate().y + 20.f);

	mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
	aimDir = mousePosition - playerCenter;
	aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
	float pi = 3.14159265f;
	float deg = atan2(aimDirNorm.y, aimDirNorm.x) * 180 / pi;
	playerHandRight.setRotation(deg);
}
