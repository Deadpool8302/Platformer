#pragma once
#include<SFML/Graphics.hpp>
#include"Platform.hpp"

class Camera{
private:
	sf::Vector2f center;
	sf::Vector2f shift;

public:
	Camera(sf::Vector2f);

	void update(sf::Vector2f);
	void apply(sf::RectangleShape&);
	void apply(sf::FloatRect&);
};
