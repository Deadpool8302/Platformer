#pragma once
#include"SFML/Graphics.hpp"
#include<iostream>
#include<unordered_map>

class Platform {
private:
	sf::RectangleShape hitbox;
	sf::Sprite* img;
	bool isSingle;

public:
	Platform(sf::Vector2f, sf::Vector2f);
	~Platform();

	bool isHit(sf::FloatRect);
	void move(sf::Vector2f);

	sf::FloatRect getGlobalBounds();

	sf::RectangleShape& getHitbox();

	void updateSprite();
	void loadTiles(sf::Vector2f&, std::unordered_map<std::string, sf::Texture>&);

	static std::vector<Platform*> plats;
	static void add(sf::Vector2f,sf::Vector2f, sf::Vector2f&, std::unordered_map<std::string, sf::Texture>&);
	static void drawAll(sf::RenderWindow&);
	static void deleteAll();
	
	
};


