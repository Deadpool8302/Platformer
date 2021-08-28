#include "Platform.hpp"


std::vector<Platform*> Platform::plats;

Platform::Platform(sf::Vector2f pos, sf::Vector2f size) :
	hitbox(size), isSingle(true), img(nullptr)
{	
	hitbox.setPosition(pos);
	hitbox.setFillColor(sf::Color::Green);
}

Platform::~Platform()
{
	if (isSingle) delete img;
	else delete[] img;
}


bool Platform::isHit(sf::FloatRect obj)
{
	return obj.intersects(hitbox.getGlobalBounds());
}

void Platform::move(sf::Vector2f pos)
{
	hitbox.move(pos);
	updateSprite();
}


void Platform::drawAll(sf::RenderWindow& win)
{
	for (int i = 0; i < Platform::plats.size(); i++) {
		win.draw(*(plats[i]->img));
		if (!plats[i]->isSingle) {  
			win.draw(plats[i]->img[1]);
			win.draw(plats[i]->img[2]);
		}
	}
}

void Platform::deleteAll()
{
	for (int i = 0; i < plats.size(); i++) {
		delete plats[i];
	}
	plats.clear();
}

sf::FloatRect Platform::getGlobalBounds()
{
	return hitbox.getGlobalBounds();
}

sf::RectangleShape& Platform::getHitbox()
{
	return hitbox;
}

void Platform::updateSprite()
{ 
	img->setPosition(hitbox.getPosition());
	if (!isSingle) {
		img[1].setPosition(hitbox.getPosition() + sf::Vector2f(0, img[0].getGlobalBounds().height));
		img[2].setPosition(hitbox.getPosition() + sf::Vector2f(0, img[0].getGlobalBounds().height + img[1].getGlobalBounds().height));
	}
} 

void Platform::loadTiles(sf::Vector2f& tileSize, std::unordered_map<std::string, sf::Texture>& allTextures)
{
	int tSize = tileSize.y;
	if (hitbox.getSize().y == tileSize.y) { 
		img = new sf::Sprite;
		img->setTexture(allTextures["tile"]);
		img->setTextureRect({ 0,0,(int)hitbox.getSize().x, tSize });
	}
	else {
		img = new sf::Sprite[3];
		isSingle = false;
		img[0].setTexture(allTextures["topTile"]);
		img[0].setTextureRect({ 0,0,(int)hitbox.getSize().x, tSize });
		img[1].setTexture(allTextures["midTile"]);
		img[1].setTextureRect({ 0,0,(int)hitbox.getSize().x, (int)hitbox.getSize().y - 2*tSize});
		img[2].setTexture(allTextures["bottomTile"]); 
		img[2].setTextureRect({ 0,0,(int)hitbox.getSize().x, tSize });
	}

	updateSprite();
}

void Platform::add(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f& tileSize, std::unordered_map<std::string,sf::Texture>& allTextures)
{
	plats.push_back(new Platform(pos, size));
	plats.back()->loadTiles(tileSize, allTextures);
}
 
