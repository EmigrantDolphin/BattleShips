/*
this is used in PlaceShips class, to visualize the amount of ships left;
draws ShipSize::n rectangles in specified position and write xM how many left;
*/

#ifndef _SHIPCREATIONCOUNTERH_
#define _SHIPCREATIONCOUNTERH_

#include <SFML/Graphics.hpp>
#include "GameMaster.h"
#include "IDrawable.h"
#include "IClickable.h"
#include "BattleField.h"
class ShipCreationCounter : public IDrawable, public IClickable{
public:
	enum ShipSize {Two, Three, Four, Five};
private:
	sf::RectangleShape *rect;
	sf::Font font;
	sf::Text text;
	BattleField::ShipSize shipSize = BattleField::ShipSize::Two;
	float posX = 0, posY = 0;
	float rectSize = 30;
	float rectThickness = 1;
	BattleField::ShipSize *selectedShip;
	
	float getShipWidth();
	void refresh();
public:
	ShipCreationCounter(BattleField::ShipSize, int, BattleField::ShipSize *);
	~ShipCreationCounter();
	void setShipsLeft(int);
	void setPos(float, float);
	void setSize(float);
	bool isMouseOver();
	void onMouseClick();
	void select();
	void deselect();
	float getWidth();
	float getHeight();
	void draw(sf::RenderWindow &);
};

#endif