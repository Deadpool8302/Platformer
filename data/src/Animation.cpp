#include "Animation.hpp"

Animation::Animation(sf::Texture& texture, int mFrame, const sf::Vector2f& fSize, int yOffset) :
	frame(0), maxFrame(mFrame), frameSize(fSize),animSpeed(50), count(0)
{
	img.setTexture(texture);
	img.setTextureRect({ 0, yOffset * (int)frameSize.y, (int)frameSize.x, (int)frameSize.y });

}


void Animation::draw(sf::RenderWindow& win)
{
	win.draw(img);
}

void Animation::setScale(float x, float y)
{
	img.setScale(x, y);
}

sf::Vector2f Animation::getScale()
{
	return img.getScale();
}

void Animation::animate()
{
	sf::IntRect rect = img.getTextureRect();
	img.setTextureRect({ rect.width*frame, rect.top, rect.width, rect.height });
	frame++;
	if (frame > maxFrame) frame = 0;

	
}
void Animation::reset()
{
	frame = 0;
}

void Animation::setPosition(const sf::Vector2f& pos)
{
	img.setPosition(pos);
}

void Animation::setCenter()
{
	img.setOrigin(img.getLocalBounds().width/2,img.getLocalBounds().height/2);
}

void Animation::setSpeed(int s)
{
	animSpeed = s;
}
