#pragma once
#include<SFML/Graphics.hpp>
#include"Player.hpp"
#include"Camera.hpp"
#include"Platform.hpp"
#include<vector>
#include<unordered_map>

class Game {
private:
	sf::RenderWindow window;
	sf::Vector2f tileSize;
	sf::Vector2f winSize;
	Player player;
	bool isPaused;
	Camera cam;
	std::unordered_map<std::string, sf::Texture> allTextures;
	sf::Sprite bgImg;

	sf::FloatRect lvlBound;
	int curLevel;
	int totalLevels;

public:
	Game();
	~Game();

	void update();
	void render();

	void pollEvents();
	bool isRunning();
	std::pair<bool,bool> isBounded();

	void loadLevel(int);

	sf::Vector2f getWinsize();
};

