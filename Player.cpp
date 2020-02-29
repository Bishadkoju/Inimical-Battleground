#include "Player.h"

Player::Player():isPressedLeft(false),isPressedRight(false),isPressedUp(false),isCollided(false),isOnGround(false)
{
	
	/*isPressedLeft = false;
	isPressedRight = false;
	isPressedUp = false;
	isCollided = false;
	isOnGround = false;*/
	/*this->arena1 = &arena1;
	this->noOfBlocks = this->arena1->noOfBlocks;*/

	coordinate.x = 200;
	coordinate.y = 200;
	currentVelocity.x = 0;
	currentVelocity.y = 0;
	targetVelocity.x = 0;
	targetVelocity.y = 0;
	maxGroundVelocity.x =20;
	maxAirVelocity.x = 60;
	maxAirVelocity.y = 80;
	thrustValue = 80;

	texture.loadFromFile("pic/army1.png");
	scale = 1;
	body.setSize(sf::Vector2f(10.f, 10.f));
	//body.setRotation(60.f);

	groundDampingConstant = 500;
	airDampingConstant = 50;
	gravity = 50;
	elasticConstant = 0.3f;
	collider = (new Collider(body));
	//collider.body = this->body;

	noKeyWasPressed = true;
	//directions
	facingRight = true;
	//facingLeft = false;
	//animations spritesheet
	animations[int(AnimationIndex::flyingright)] = Animation(0, 152, 95, 150, "right");
	animations[int(AnimationIndex::flyingleft)] = Animation(0, 152, 95, 150, "left");
	animations[int(AnimationIndex::walkingright)] = Animation(0, 0, 95, 150, "right");
	animations[int(AnimationIndex::walkingleft)] = Animation(0, 0, 95, 150, "left");
	animations[int(AnimationIndex::standingright)] = Animation(0, 0, 95, 150, "stillright");
	animations[int(AnimationIndex::standingleft)] = Animation(0, 167, 95, 150, "stillleft");
	lhand.loadFromFile("pic/rhandinverse.png");
	rhand.loadFromFile("pic/rhand.png");//animations[int(AnimationIndex::standing)] = Animation(0, 0, 95, 150, "left", noKeyWasPressed);
	
	playerHandLeft.setTexture(lhand);
	playerHandRight.setTexture(rhand);
	spritePlayer.setScale(scale, scale);
	playerHandLeft.setScale(scale, scale);
	playerHandRight.setScale(scale,scale);

	//arena_blocks[0].setFillColor(sf::Color(100, 250, 50));
	//arena_blocks[0].setSize(sf::Vector2f(100, 50));
	//arena_blocks[0].setPosition(900, 450);

}



void Player::update(sf::Time deltaTime,playerController userController)
{
	
	this->deltaTime = deltaTime;
	this->isPressedLeft = userController.isPressedLeft;
	this->isPressedRight = userController.isPressedRight;
	this->isPressedUp = userController.isPressedUp;
	this->isLeftMouseButtonPressed = userController.isLeftMouseButtonPressed;
	this->isRightMouseButtonPressed = userController.isRightMouseButtonPressed;
	this->mousePosition = userController.mousePosition;

	//std::cout << mousePosition.x << "," << mousePosition.y << "||"<<mouseDirection.x << "," << mouseDirection.y << std::endl;
	isOnGround = currentVelocity.y == 0;
	noKeyWasPressed = !(isPressedLeft || isPressedRight || isPressedUp);
	if (isOnGround) {
		movePlayer(maxGroundVelocity, groundDampingConstant);
		//std::cout << "Ground" << std::endl;
		}
	else {
		movePlayer(maxAirVelocity, airDampingConstant);
		//std::cout << "Air"<< std::endl;
	}

	setBulletDir();
	if (isLeftMouseButtonPressed && localTime.getElapsedTime().asSeconds()>0.4f) {
		if (facingRight == true) {
			bullets.emplace_back(Bullet(playerHandRight.getPosition(), mouseDirection, 1000, 50));
		}
		else {
			sf::Vector2f temp = playerHandLeft.getPosition();
			temp.x=playerHandLeft.getPosition().x ;
			bullets.emplace_back(Bullet(temp, mouseDirection, 1000, 50));
		}
		localTime.restart();

	}
		for (auto& bullet : bullets)
		{
			bullet.update(deltaTime);

		}
	

	

	
	
	for (const auto block : arena1->blocks) {
		handlePlayerCollision(block);
	}
	/*for (int i = 0; i < noOfBlocks; i++) {
		handlePlayerCollision(arena1->blocks[i]);
	}*/


	
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
	for (auto& bullet : bullets)
	{
		bullet.draw(window);
	}

	if (!facingRight) {
		curAnimation = AnimationIndex::walkingleft;
		if (noKeyWasPressed)
		{
			curAnimation = AnimationIndex::standingleft;
		}
	}
	if (facingRight) {
		curAnimation = AnimationIndex::walkingright;
		if (noKeyWasPressed)
		{
			curAnimation = AnimationIndex::standingright;
		}
	}
	if (!isOnGround) {
		if (((isPressedUp ||isPressedLeft ||isPressedRight) && !facingRight)) {
			curAnimation = AnimationIndex::flyingleft;
		}
		if (((isPressedUp || isPressedLeft || isPressedRight) && facingRight)) {
			curAnimation = AnimationIndex::flyingright;
		}
	}

	if (!(noKeyWasPressed)) {
		animations[int(curAnimation)].update(deltaTime);
	}
	animations[int(curAnimation)].applySprite(spritePlayer);
	body.setFillColor(sf::Color(100, 250, 50));
	body.setSize(sf::Vector2f(100, 150));
	window.draw(body);

	


	
	
	spritePlayer.setPosition(getCoordinate().x, getCoordinate().y);
	window.draw(spritePlayer);

	if (!facingRight)
	{
		/*playerHandLeft.setOrigin({
			playerHandLeft.getGlobalBounds().width / 2 + playerHandLeft.getOrigin().x,
			playerHandLeft.getGlobalBounds().height / 2 + playerHandLeft.getOrigin().y
			});*/


		playerHandLeft.setPosition(getCoordinate().x - 40 + playerHandLeft.getLocalBounds().width,
			getCoordinate().y + 63 + playerHandLeft.getLocalBounds().height);
		window.draw(playerHandLeft);
	}
	if (facingRight)
	{
		playerHandRight.setPosition(spritePlayer.getPosition().x + spritePlayer.getLocalBounds().height*0.15*scale, spritePlayer.getPosition().y +spritePlayer.getLocalBounds().width*0.75*scale);
		window.draw(playerHandRight);
	}



	


}

void Player::setArena(Arena& arena)
{
	arena1 = &arena;
}


void Player::handlePlayerCollision(sf::RectangleShape other)
{
	if (collider->checkCollision((other))) {
		if (collider->intersection.height < collider->intersection.width) {
			if (body.getGlobalBounds().top < other.getGlobalBounds().top) {
				coordinate.y -= collider->intersection.height;
				if (abs(currentVelocity.y) < 1) { currentVelocity.y = 0; }
				currentVelocity.y = -elasticConstant * currentVelocity.y;
				targetVelocity.y = 0;
			}
			else {
				coordinate.y += collider->intersection.height;
				if (abs(currentVelocity.y) < 1) { currentVelocity.y = 0; }
				currentVelocity.y = -elasticConstant * currentVelocity.y;
				targetVelocity.y = currentVelocity.y;
			}
		}

		if (collider->intersection.height > collider->intersection.width) { //horizontal collission

			if (body.getGlobalBounds().left < other.getGlobalBounds().left) {
				coordinate.x -= collider->intersection.width;
				currentVelocity.x = -elasticConstant * currentVelocity.x;
				targetVelocity.x = currentVelocity.x;
			}
			else {
				coordinate.x += collider->intersection.width;
				currentVelocity.x = -elasticConstant * currentVelocity.x;
				targetVelocity.x = currentVelocity.x;
			}
		}
		body.setPosition(coordinate);


	}
}

void Player::movePlayer(sf::Vector2f maxVelocity, float dampingConstant)
{

	if (isPressedLeft) {
		targetVelocity.x = -maxVelocity.x;

		/*facingLeft = true;
		facingRight = false;*/
	}
	else if (isPressedRight) {
		targetVelocity.x = maxVelocity.x;
		/*facingRight = true;
		facingLeft = false;*/
	}
	else {
		targetVelocity.x = 0;
	}

	if (isPressedUp) {
		if (fuel>100||(fuel>1 &&currentVelocity.y<0)) {
			targetVelocity.y -= deltaTime.asSeconds() * thrustValue;
			fuel -= thrustValue*5 * deltaTime.asSeconds();
		}
		else {
			fuel -= thrustValue * 5 * deltaTime.asSeconds();
		}

	}
	targetVelocity.y += deltaTime.asSeconds() * gravity;
	fuel += 60 * deltaTime.asSeconds();
	if (fuel > 1000) fuel = 1000;
	if (fuel < 0) fuel = 0;
	std::cout << fuel << std::endl;

	currentVelocity.x = interpolateVelocity(targetVelocity.x, currentVelocity.x, dampingConstant);
	currentVelocity.y = interpolateVelocity(targetVelocity.y, currentVelocity.y, dampingConstant);
	coordinate.x += currentVelocity.x * 5 * deltaTime.asSeconds();
	coordinate.y += currentVelocity.y * 5 * deltaTime.asSeconds();
	body.setPosition(coordinate);
}




void Player::setBulletDir()
{
	if (facingRight) {
		playerCenter = playerHandRight.getPosition();
	}
	else {
		playerCenter = playerHandLeft.getPosition();
	}

	//mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
	mouseDirection = mousePosition - playerCenter;
	mouseDirection = mouseDirection / sqrt(pow(mouseDirection.x, 2) + pow(mouseDirection.y, 2));
	float pi = 3.14159265f;
	float deg = atan2(mouseDirection.y, mouseDirection.x) * 180 / pi;


	if (facingRight)
	{
		playerHandRight.setRotation(deg);
		if (deg < -90 || deg>90)
		{
			
			facingRight = false;
		}
	}
	if (!facingRight)
	{
		playerHandLeft.setRotation(deg);
		if (!(deg < -90 || deg>90))
		{
			
			facingRight = true;
		}
	}


	

}
