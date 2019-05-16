#ifndef _IDRAWABLEH_
#define _IDRAWABLEH_

#include <SFML/Graphics.hpp>

class IDrawable {
public:
	virtual void draw() = 0;
};

#endif