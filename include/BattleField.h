#ifndef _BATTLEFIELDH_
#define _BATTLEFIELDH_

#include <SFML/Graphics.hpp>
#include "GameMaster.h"
#include <RectShapeEnh.h>
#include <iostream>
class BattleField{
public:
	enum EditState {Horizontal, Vertical, Erase, None};
	enum ShipSize {Two, Three, Four, Five};
private:
	EditState editState = EditState::None;
	ShipSize selectedShipSize = ShipSize::Five;
	ShipSize lastErasedShipSize = ShipSize::Two;

	float posX = 10, posY = 10;
	static const int FieldWidth = 10, FieldHeight = 10, RectSize = 30, RectThickness = 1;
	RectShapeEnh fieldArr[FieldWidth][FieldHeight];
	sf::RectangleShape fieldBounds; // to make edges same as inner lines
	sf::Text playerNameT;
	sf::Color nameColor;
	sf::Font font;
	std::string playerNameS;
	
	sf::Vector2i selectedRectPos;
	
	//temp, running out of time
	int const totalShips = 10;
	int currentDeadShips = 0;
	
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
	
	void onHitAlive();
	int aliveCellCount(int, int);
	void makeShipDead(int, int);
	
	
public:
	BattleField(std::string);
	void draw(sf::RenderWindow &);
	void setPos(float, float);
	sf::Vector2f getPos();
	float getWidthHeight();
	float getFieldWidth();
	float getFieldHeight();
	void setEditState(EditState);
	BattleField::EditState getEditState();
	void setSelectedShipSize(ShipSize);
	BattleField::ShipSize* getSelectedShipRef();
	BattleField::ShipSize getSelectedShipSize();
	BattleField::ShipSize getLastDeletedShipSize();
	bool placeShip();
	bool deleteShip();
	void shipVisibility(bool);
	RectShapeEnh::State hit();
	void setNameColor(sf::Color);
	void setNameText(std::string);
	int getDeadShipCount();
	int getTotalShipCount();
	void setSelectedRectPos(int, int);
	
	RectShapeEnh& getFieldCell(int, int);
	
	void printConsole();
};

#endif