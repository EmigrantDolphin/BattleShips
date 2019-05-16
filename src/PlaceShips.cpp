#include "PlaceShips.h"

PlaceShips::PlaceShips(sf::RenderWindow *window, BattleField *battleField){
	this->window = window;
	this->battleField = battleField;
	init();
}

void PlaceShips::init(){
	float x = window->getSize().x / 2 - battleField->getWidthHeight() /2;
	float y = (window->getSize().y - battleField->getWidthHeight()) / 2;
	battleField->setPos(x, y);
	this->selectedShip = battleField->getSelectedShipRef();
	
	
	this->twoShipCounter = new ShipCreationCounter(BattleField::ShipSize::Two, twoShipCountI, window, selectedShip);
	this->threeShipCounter = new ShipCreationCounter(BattleField::ShipSize::Three, threeShipCountI, window, selectedShip);
	this->fourShipCounter = new ShipCreationCounter(BattleField::ShipSize::Four, fourShipCountI, window, selectedShip);
	this->fiveShipCounter = new ShipCreationCounter(BattleField::ShipSize::Five, fiveShipCountI, window, selectedShip);
	
	twoShipCounter->setPos(counterPosX, counterPosY);
	twoShipCounter->setSize(counterRectSize);
	threeShipCounter->setPos(counterPosX, counterPosY + counterOffset + counterRectSize);
	threeShipCounter->setSize(counterRectSize);
	fourShipCounter->setPos(counterPosX, counterPosY + (counterOffset + counterRectSize) * 2);
	fourShipCounter->setSize(counterRectSize);
	fiveShipCounter->setPos(counterPosX, counterPosY + (counterOffset + counterRectSize) * 3);
	fiveShipCounter->setSize(counterRectSize);
	
	shipCountersDrawable[0] = twoShipCounter;
	shipCountersDrawable[1] = threeShipCounter;
	shipCountersDrawable[2] = fourShipCounter;
	shipCountersDrawable[3] = fiveShipCounter;
	
	shipCountersClickable[0] = twoShipCounter;
	shipCountersClickable[1] = threeShipCounter;
	shipCountersClickable[2] = fourShipCounter;
	shipCountersClickable[3] = fiveShipCounter;
}



void PlaceShips::onKeyPress(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		battleField->setEditState(BattleField::EditState::Horizontal);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		battleField->setEditState(BattleField::EditState::Vertical);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		battleField->setEditState(BattleField::EditState::Erase);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		battleField->setSelectedShipSize(BattleField::ShipSize::Two);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		battleField->setSelectedShipSize(BattleField::ShipSize::Three);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		battleField->setSelectedShipSize(BattleField::ShipSize::Four);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		battleField->setSelectedShipSize(BattleField::ShipSize::Five);
}

void PlaceShips::onMouseClick(){
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return;
	
	if (haveShip() && battleField->placeShip()){
		shipPlaced(battleField->getSelectedShipSize());
	}
	
	if (battleField->deleteShip())
		shipDeleted(battleField->getLastDeletedShipSize());
	
	for (int i = 0; i < countersI; i++)
		shipCountersClickable[i]->onMouseClick();
	
}


bool PlaceShips::haveShip(){
	if (battleField->getSelectedShipSize() == BattleField::ShipSize::Two && twoShipCountI > 0)
		return true;
	if (battleField->getSelectedShipSize() == BattleField::ShipSize::Three && threeShipCountI > 0)
		return true;
	if (battleField->getSelectedShipSize() == BattleField::ShipSize::Four && fourShipCountI > 0)
		return true;
	if (battleField->getSelectedShipSize() == BattleField::ShipSize::Five && fiveShipCountI > 0)
		return true;
	return false;
}

void PlaceShips::shipDeleted(BattleField::ShipSize shipSize){
	if (shipSize == BattleField::ShipSize::Two)
		twoShipCountI++;
	if (shipSize == BattleField::ShipSize::Three)
		threeShipCountI++;
	if (shipSize == BattleField::ShipSize::Four)
		fourShipCountI++;
	if (shipSize == BattleField::ShipSize::Five)
		fiveShipCountI++;
	twoShipCounter->setShipsLeft(twoShipCountI);
	threeShipCounter->setShipsLeft(threeShipCountI);
	fourShipCounter->setShipsLeft(fourShipCountI);
	fiveShipCounter->setShipsLeft(fiveShipCountI);
}

void PlaceShips::shipPlaced(BattleField::ShipSize shipSize){
	if (shipSize == BattleField::ShipSize::Two)
		twoShipCountI--;
	if (shipSize == BattleField::ShipSize::Three)
		threeShipCountI--;
	if (shipSize == BattleField::ShipSize::Four)
		fourShipCountI--;
	if (shipSize == BattleField::ShipSize::Five)
		fiveShipCountI--;
	twoShipCounter->setShipsLeft(twoShipCountI);
	threeShipCounter->setShipsLeft(threeShipCountI);
	fourShipCounter->setShipsLeft(fourShipCountI);
	fiveShipCounter->setShipsLeft(fiveShipCountI);
}

void PlaceShips::draw(){
	onKeyPress();
	onMouseClick();
	
	for (int i = 0; i < countersI; i++)
		shipCountersDrawable[i]->draw();
	battleField->draw();
	
	
}