#include "Camera.hpp"


Camera::Camera(sf::Vector2f pos)
{
	center = pos;
}


void Camera::update(sf::Vector2f pos)
{
	shift = center - pos;
}

void Camera::apply(sf::RectangleShape& rect)
{
	rect.move(shift);
}

void Camera::apply(sf::FloatRect& bound)
{
	bound.left += shift.x;
	bound.top += shift.y;
}
