#ifndef _SHIPCREATIONCOUNTERH_
#define _SHIPCREATIONCOUNTERH_

#include <SFML/Graphics.hpp>


class ShipCreationCounter{
public:
	enum ShipSize {Two, Three, Four, Five};
private:
	sf::RenderWindow *window;
	sf::RectangleShape *rect;
	sf::Font font;
	sf::Text text;
	ShipSize shipSize = ShipSize::Two;
	float posX = 0, posY = 0;
	float rectSize = 30;
	float rectThickness = 1;
	
	float getShipWidth();
	void refresh();
public:
	ShipCreationCounter(ShipCreationCounter::ShipSize, int, sf::RenderWindow *);
	void setShipsLeft(int);
	void setPos(float, float);
	void setSize(float);
	float getRectSize();
	void draw();
};

#endif