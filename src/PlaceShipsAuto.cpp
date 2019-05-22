#include "PlaceShipsAuto.h"


PlaceShipsAuto::PlaceShipsAuto(BattleField *bf){
	this->battleField = bf;
	srand(time(NULL));
	
	for (int i = 0; i < battleField->getFieldHeight(); i++)
		for (int j = 0; j < battleField->getFieldWidth(); j++)
			if (randCurrentShipSize() && (rand() % 2 == 1)){
				randEditState();
				battleField->setSelectedRectPos(j, i);
				battleField->setSelectedShipSize(currentShipSize);
				//std::cout << "twoship " << twoShipCountI << std::endl;
				if(battleField->placeShip())
					switch (currentShipSize){
						case BattleField::ShipSize::Two : twoShipCountI--; break;
						case BattleField::ShipSize::Three : threeShipCountI--; break;
						case BattleField::ShipSize::Four : fourShipCountI--; break;
						case BattleField::ShipSize::Five : fiveShipCountI--; break;
					}
			}
	
	for (int i = 0; i < battleField->getFieldHeight(); i++)
		for (int j = 0; j < battleField->getFieldWidth(); j++)
			if (randCurrentShipSize()){
				randEditState();
				battleField->setSelectedRectPos(j, i);
				battleField->setSelectedShipSize(currentShipSize);
				//std::cout << "twoship " << twoShipCountI << std::endl;
				if(battleField->placeShip())
					switch (currentShipSize){
						case BattleField::ShipSize::Two : twoShipCountI--; break;
						case BattleField::ShipSize::Three : threeShipCountI--; break;
						case BattleField::ShipSize::Four : fourShipCountI--; break;
						case BattleField::ShipSize::Five : fiveShipCountI--; break;
					}
			}
	battleField->printConsole();
	battleField->setSelectedRectPos(-1, -1);
}

int PlaceShipsAuto::getShipsLeft(){
	return twoShipCountI+threeShipCountI+fourShipCountI+fiveShipCountI;
}

bool PlaceShipsAuto::randCurrentShipSize(){
	std::vector<BattleField::ShipSize> pool;
	
	if (twoShipCountI > 0)
		pool.push_back(BattleField::ShipSize::Two);
	if (threeShipCountI > 0)
		pool.push_back(BattleField::ShipSize::Three);
	if (fourShipCountI > 0)
		pool.push_back(BattleField::ShipSize::Four);
	if (fiveShipCountI > 0)
		pool.push_back(BattleField::ShipSize::Five);
	
	if (pool.size() == 0)
		return false;
	
	currentShipSize = pool[rand() % pool.size()];
	return true;	
}

void PlaceShipsAuto::randEditState(){
	switch (rand()%2){
		case 0 : battleField->setEditState(BattleField::EditState::Horizontal); break;
		case 1 : battleField->setEditState(BattleField::EditState::Vertical); break;
	}
}
