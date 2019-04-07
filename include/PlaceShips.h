#ifndef _PLACESHIPSH_
#define _PLACESHIPSH_

#include <SFML/Graphics.hpp>
#include "BattleField.h"
#include "ShipCreationCounter.h"

class PlaceShips{
private:
	sf::RenderWindow *window;
	BattleField *battleField;
	ShipCreationCounter *twoShipCounter, *threeShipCounter, *fourShipCounter, *fiveShipCounter;
	int counterPosX = 10, counterPosY = 10, counterOffset = 10, counterSize = 30;
	int twoShipI = 4, threeShipI = 3, fourShipI = 2, fiveShipI = 1;
	sf::Text twoShipT, threeShipT, fourShipT, fiveShipT;
	
	void init();
	void onKeyPress();
	void onMouseClick();
	bool haveShip();
	void shipPlaced(BattleField::ShipSize);
	void shipDeleted(BattleField::ShipSize);
public:
	PlaceShips(sf::RenderWindow *, BattleField *);
	void draw();
};

#endif