#pragma once 
#include"SFML/Graphics.hpp"

class Animation {
private:
	sf::Sprite img;
	int frame;
	int maxFrame;
	sf::Vector2u frameSize;
	int animSpeed;
	int count;

public:
	Animation(sf::Texture&, int, const sf::Vector2f&, int = 0);

	void setPosition(const sf::Vector2f&);
	void setCenter();
	void setSpeed(int);

	void animate();
	void reset();
	void setScale(float, float);
	sf::Vector2f getScale();
	void draw(sf::RenderWindow&);
};
