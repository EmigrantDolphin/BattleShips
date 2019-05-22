/*
you pass a BattleField pointer to this class, and are able to edit that battlefield;
placing ships, deleting ships etc. And becuase you pass a pointer, battlefield 
is populated directly
*/

#ifndef _PLACESHIPSH_
#define _PLACESHIPSH_

#include <SFML/Graphics.hpp>
#include "GameMaster.h"
#include "BattleField.h"
#include "ShipCreationCounter.h"
#include "IDrawable.h"
#include "Button.h"
#include <vector>

class PlaceShips : public IDrawable{
private:
	BattleField *battleField;
	std::vector<IDrawable *> drawables;
	std::vector<IClickable *> clickables;
	ShipCreationCounter *twoShipCounter, *threeShipCounter, *fourShipCounter, *fiveShipCounter;
	const int counterPosX = 10, counterPosY = 10, counterOffset = 10, counterRectSize = 30;
	int twoShipCountI = 4, threeShipCountI = 3, fourShipCountI = 2, fiveShipCountI = 1;
	BattleField::ShipSize *selectedShip;
	
	Button *HButton, *VButton, *EButton;
	float buttonOffset = 20;
	
	Button *exitButton;
	
	bool *isSetup;

	void init();
	void onKeyPress();
	void onMouseClick();
	bool haveShip();
	void shipPlaced(BattleField::ShipSize);
	void shipDeleted(BattleField::ShipSize);
	
public:
	PlaceShips(BattleField *, bool *);
	~PlaceShips();
	void draw(sf::RenderWindow &);
};

#endif