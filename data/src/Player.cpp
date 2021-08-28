#include "Player.hpp"
#include<iostream>


Player::Player():
	hitbox({ 70,70 }), v({ 0.5,0 }), g(0.005), a({ 0.5,g }), currState(IDLE)
{
	
}

Player::~Player()
{
	delete anim[0];
	delete anim[1];
}

void Player::create(const sf::Vector2f& pos)
{
	hitbox.setOrigin(hitbox.getSize() / 2.f);
	hitbox.setPosition(pos);
	hitbox.setFillColor(sf::Color::Transparent);

	hitbox.setOutlineColor(sf::Color::Green);
	hitbox.setOutlineThickness(-2);

	ninja.loadFromFile("data/assets/images/ninja.png");
	anim[0] = new Animation(ninja, 9, sf::Vector2f(ninja.getSize().x / 10, ninja.getSize().y / 2), 0);
	anim[0]->setCenter();
	anim[0]->setScale(hitbox.getSize().x / 363, hitbox.getSize().y / 458);

	anim[1] = new Animation(ninja, 9, sf::Vector2f(ninja.getSize().x / 10, ninja.getSize().y / 2), 1);
	anim[1]->setCenter();
	anim[1]->setScale(hitbox.getSize().x / 363, hitbox.getSize().y / 458);

	currAnim = anim[0];
	updateSprite();
}

void Player::updateSprite()
{
	currAnim->setPosition(hitbox.getPosition());
}

void Player::updateAnim(State state)
{
	currAnim->reset();
	currState = state;
	if (state == IDLE) currAnim = anim[0];
	if (state == RUNNING) currAnim = anim[1];
}

void Player::setDir(int x)
{
	v.x = x * abs(v.x);
	currAnim->setScale(x*abs(currAnim->getScale().x),currAnim->getScale().y);
}

int Player::getDir()
{
	return v.x/abs(v.x);
}


void Player::move()
{
	hitbox.move(v.x, 0);

	Platform* check = checkCollision();
	if (check != nullptr) {
		sf::FloatRect temp = check->getGlobalBounds();
		if (v.x > 0) hitbox.setPosition(temp.left - hitbox.getSize().x / 2, hitbox.getPosition().y);
		else if (v.x < 0) hitbox.setPosition(temp.left+temp.width + hitbox.getSize().x / 2, hitbox.getPosition().y);
	}
	
	updateSprite();
} 

void Player::jump()
{
	if (v.y == 0) v.y = -1.5;
}

Platform* Player::checkCollision()
{
	for (int i = 0; i < Platform::plats.size(); i++) {
		if (Platform::plats[i]->isHit(hitbox.getGlobalBounds())) return Platform::plats[i];
	}
	return nullptr;
}

sf::Vector2f Player::getposition()
{
	return hitbox.getPosition();
}

sf::RectangleShape& Player::getHitbox()
{
	return hitbox;
}

void Player::update()
{
	float s = (v.y) + g / 2.f;
	v.y = v.y + g; 

	hitbox.move(0, s);

	//checking collision............................................................................................
	Platform* check = checkCollision();
	if (check != nullptr) {
		sf::FloatRect temp = check->getGlobalBounds();
		if (v.y > 0) hitbox.setPosition(hitbox.getPosition().x, temp.top - hitbox.getSize().y / 2);
		else if (v.y < 0) hitbox.setPosition(hitbox.getPosition().x, temp.top + temp.height + hitbox.getSize().y/2);
		v.y = 0;
	}
	//..............................................................................................................

	currAnim->animate();
	updateSprite();
}



void Player::draw(sf::RenderWindow& win)
{
	currAnim->draw(win);
	//win.draw(hitbox);
}


