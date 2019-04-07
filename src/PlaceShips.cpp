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
	
	
	this->twoShipCounter = new ShipCreationCounter(ShipCreationCounter::ShipSize::Two, twoShipI, window);
	this->threeShipCounter = new ShipCreationCounter(ShipCreationCounter::ShipSize::Three, threeShipI, window);
	this->fourShipCounter = new ShipCreationCounter(ShipCreationCounter::ShipSize::Four, fourShipI, window);
	this->fiveShipCounter = new ShipCreationCounter(ShipCreationCounter::ShipSize::Five, fiveShipI, window);
	
	twoShipCounter->setPos(counterPosX, counterPosY);
	twoShipCounter->setSize(counterSize);
	threeShipCounter->setPos(counterPosX, counterPosY + counterOffset + counterSize);
	threeShipCounter->setSize(counterSize);
	fourShipCounter->setPos(counterPosX, counterPosY + (counterOffset + counterSize) * 2);
	fourShipCounter->setSize(counterSize);
	fiveShipCounter->setPos(counterPosX, counterPosY + (counterOffset + counterSize) * 3);
	fiveShipCounter->setSize(counterSize);
	
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
	
}

bool PlaceShips::haveShip(){
	if (battleField->getSelectedShipSize() == BattleField::ShipSize::Two && twoShipI > 0)
		return true;
	if (battleField->getSelectedShipSize() == BattleField::ShipSize::Three && threeShipI > 0)
		return true;
	if (battleField->getSelectedShipSize() == BattleField::ShipSize::Four && fourShipI > 0)
		return true;
	if (battleField->getSelectedShipSize() == BattleField::ShipSize::Five && fiveShipI > 0)
		return true;
	return false;
}

void PlaceShips::shipDeleted(BattleField::ShipSize shipSize){
	if (shipSize == BattleField::ShipSize::Two)
		twoShipI++;
	if (shipSize == BattleField::ShipSize::Three)
		threeShipI++;
	if (shipSize == BattleField::ShipSize::Four)
		fourShipI++;
	if (shipSize == BattleField::ShipSize::Five)
		fiveShipI++;
	twoShipCounter->setShipsLeft(twoShipI);
	threeShipCounter->setShipsLeft(threeShipI);
	fourShipCounter->setShipsLeft(fourShipI);
	fiveShipCounter->setShipsLeft(fiveShipI);
}

void PlaceShips::shipPlaced(BattleField::ShipSize shipSize){
	if (shipSize == BattleField::ShipSize::Two)
		twoShipI--;
	if (shipSize == BattleField::ShipSize::Three)
		threeShipI--;
	if (shipSize == BattleField::ShipSize::Four)
		fourShipI--;
	if (shipSize == BattleField::ShipSize::Five)
		fiveShipI--;
	twoShipCounter->setShipsLeft(twoShipI);
	threeShipCounter->setShipsLeft(threeShipI);
	fourShipCounter->setShipsLeft(fourShipI);
	fiveShipCounter->setShipsLeft(fiveShipI);
}

void PlaceShips::draw(){
	onKeyPress();
	onMouseClick();
	battleField->draw();
	twoShipCounter->draw();
	threeShipCounter->draw();
	fourShipCounter->draw();
	fiveShipCounter->draw();
	
}