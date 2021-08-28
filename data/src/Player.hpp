#pragma once
#include"SFML/Graphics.hpp"
#include"Platform.hpp"
#include"Camera.hpp"
#include"Animation.hpp"


class Player{
private:
	sf::RectangleShape hitbox;
	sf::Vector2f v, a;
	float g;
	sf::Texture ninja;
	Animation* anim[2]; 
	Animation* currAnim;
	

public:
	Player();
	~Player();
	void create(const sf::Vector2f&);

	enum State { IDLE = 0, RUNNING } currState;

	void move();
	void jump();

	Platform* checkCollision();
	sf::Vector2f getposition();
	sf::RectangleShape& getHitbox();

	void update();
	void updateSprite();
	void updateAnim(State);
	void setDir(int);
	int getDir();
	
	void draw(sf::RenderWindow&);
};
