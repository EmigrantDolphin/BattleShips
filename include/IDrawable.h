#ifndef _IDRAWABLEH_
#define _IDRAWABLEH_

#include <SFML/Graphics.hpp>

class IDrawable {
public:
	virtual void draw(sf::RenderWindow &) = 0;
};

#endif