
#include <SFML/Graphics.hpp>
#include "BattleField.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>

class PlaceShipsAuto{
	BattleField *battleField;
	BattleField::ShipSize currentShipSize;
	int twoShipCountI = 4, threeShipCountI = 3, fourShipCountI = 2, fiveShipCountI = 1;
	
	bool randCurrentShipSize();
	void randEditState();
public:
	PlaceShipsAuto(BattleField *);
	int getShipsLeft();
};