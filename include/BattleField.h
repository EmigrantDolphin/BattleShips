#ifndef _BATTLEFIELDH_
#define _BATTLEFIELDH_

#include <SFML/Graphics.hpp>
#include <RectShapeEnh.h>
#include <iostream>
class BattleField{
public:
	enum EditState {Horizontal, Vertical, Erase, None};
	enum ShipSize {Two, Three, Four, Five};
private:
	sf::RenderWindow *window;
	EditState editState = EditState::Vertical;
	ShipSize selectedShipSize = ShipSize::Five;
	ShipSize lastErasedShipSize = ShipSize::Two;

	float posX = 10, posY = 10;
	static const int FieldWidth = 10, FieldHeight = 10, RectSize = 30, RectThickness = 1;
	RectShapeEnh fieldArr[FieldWidth][FieldHeight];
	sf::RectangleShape fieldBounds; // to make edges same as inner lines

	sf::Vector2i selectedRectPos;
	
	void createField();

	int getSelectedShipSizeInt();
	void onMouseHover();
	void hoverShipH(); //used in onMouseHover to draw hovering ship, not yet placed
	void hoverShipV();
	bool doesHorizFit();
	bool doesVertiFit();
	bool isNoOneAroundH();// checks if there is no one close in a rectangle surrounding potential ship position
	bool isNoOneAroundV();
	void selectRect();
	int eraseShip(int, int);
public:
	BattleField(sf::RenderWindow *);
	void draw();
	void setPos(float, float);
	float getWidthHeight();
	void setEditState(EditState);
	void setSelectedShipSize(ShipSize);
	BattleField::ShipSize* getSelectedShipRef();
	BattleField::ShipSize getSelectedShipSize();
	BattleField::ShipSize getLastDeletedShipSize();
	bool placeShip();
	bool deleteShip();
	
};

#endif