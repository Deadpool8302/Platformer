#include "Game.hpp"
#include<iostream>
#include<fstream>
#include<sstream>

Game::Game() :
	isPaused(false), tileSize(32, 32),winSize(tileSize.x * 32, tileSize.y * 16), cam(winSize / 2.f), curLevel(1), totalLevels(1)
{

	window.setFramerateLimit(120);
	window.setVerticalSyncEnabled(false);
	window.create(sf::VideoMode(winSize.x, winSize.y), "Ninja Hattori");

	//loading textures....................................................................
	allTextures["tile"].loadFromFile("data/assets/images/singleTile.png");
	allTextures["tile"].setRepeated(true);
	allTextures["topTile"].loadFromFile("data/assets/images/topTile.png");
	allTextures["topTile"].setRepeated(true);
	allTextures["bottomTile"].loadFromFile("data/assets/images/bottomTile.png");
	allTextures["bottomTile"].setRepeated(true);
	allTextures["midTile"].loadFromFile("data/assets/images/midTile.png");
	allTextures["midTile"].setRepeated(true);
	allTextures["bgImage"].loadFromFile("data/assets/images/BG.png");
	//....................................................................................

	//setting testure of background..............
	bgImg.setTexture(allTextures["bgImage"]);
	bgImg.setScale(winSize.x / bgImg.getLocalBounds().width, winSize.y / bgImg.getLocalBounds().height);
	//...........................................

	loadLevel(1);
}

Game::~Game()
{
	Platform::deleteAll();
}

void Game::update()
{
	this->pollEvents();

	//to pause the game.............................................................
	if (isPaused) return;

	//to move the player............................................................
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.move();
	//.............................................................................. 

	player.update();
	
	std::pair<bool,bool> bound = isBounded();
	
	cam.update({
		bound.first ? winSize.x / 2.f : player.getposition().x,
		bound.second ? winSize.y / 2.f : player.getposition().y,
	});
	cam.apply(player.getHitbox());
	player.updateSprite();
	for (int i = 0; i < Platform::plats.size(); i++) {
			cam.apply(Platform::plats[i]->getHitbox());
			Platform::plats[i]->updateSprite();
	}
	cam.apply(lvlBound);

}

void Game::render()
{

	this->window.clear();

	if (!isPaused || 1) {
		//background.........................................................
		this->window.draw(bgImg);

		//platforms..........................................................
		Platform::drawAll(this->window);

		//player.............................................................
		this->player.draw(this->window);
	}
	
	this->window.display();
}

void Game::pollEvents()
{	
	sf::Event event;
	while (this->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			this->window.close();

		else if (event.type == sf::Event::KeyPressed && !isPaused) {
			if (event.key.code == sf::Keyboard::Space) player.jump();

			if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) player.updateAnim(Player::RUNNING);
			if (event.key.code == sf::Keyboard::A ) player.setDir(-1);
			if (event.key.code == sf::Keyboard::D ) player.setDir(1);
		}

		if (event.type == sf::Event::KeyReleased && !isPaused) {
			if ((event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) 
				&& !(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))) player.updateAnim(Player::IDLE);

			if (event.key.code == sf::Keyboard::A && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.setDir(1);
			if (event.key.code == sf::Keyboard::D && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.setDir(-1);
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LAlt) isPaused = !isPaused;
	}
}

bool Game::isRunning()
{
	return this->window.isOpen();
}

std::pair<bool,bool> Game::isBounded()
{
	sf::Vector2f pos(player.getposition());
	return { 
		(lvlBound.left + lvlBound.width <= winSize.x && pos.x >= winSize.x/2) || (lvlBound.left >= 0 && pos.x <= winSize.x/2),
		(lvlBound.top >= 0 && pos.y <= winSize.y / 2) || (lvlBound.top + lvlBound.height <= winSize.y && pos.y >= winSize.y / 2)
	};
}

void Game::loadLevel(int level)
{
	std::ifstream file;
	file.open("data/assets/Levels/level1.txt");
	
	std:: string s;
	while (std::getline(file, s)) {
		std::stringstream line(s);
		char type;
		line >> type;
		if (type == 'l') {
			line >> lvlBound.width >> lvlBound.height;
			lvlBound.width *= tileSize.x;
			lvlBound.height *= tileSize.y;

			lvlBound.left = lvlBound.top = 0;

			Platform::add({ lvlBound.left,0 }, { tileSize.x, lvlBound.height }, tileSize, allTextures);
			Platform::add({ lvlBound.left + lvlBound.width - tileSize.y, 0 }, { tileSize.x, lvlBound.height }, tileSize, allTextures);

		}
		else if (type == '#') {
			int x, y, w, h;
			line >> x >> y >> w >> h;
			Platform::add({ tileSize.x * x, y*tileSize.y }, { tileSize.x * w, tileSize.y*h }, tileSize, allTextures);
		}
		else if (type == 'p') {
			int x, y;
			line >> x >> y;
			player.create({ x * tileSize.x, y * tileSize.y });
		}
	}

	file.close();
}

sf::Vector2f Game::getWinsize()
{
	return this->winSize;
}
