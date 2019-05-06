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
	
	
	this->twoShipCounter = new ShipCreationCounter(ShipCreationCounter::ShipSize::Two, twoShipCountI, window, &selectedShip);
	this->threeShipCounter = new ShipCreationCounter(ShipCreationCounter::ShipSize::Three, threeShipCountI, window, &selectedShip);
	this->fourShipCounter = new ShipCreationCounter(ShipCreationCounter::ShipSize::Four, fourShipCountI, window, &selectedShip);
	this->fiveShipCounter = new ShipCreationCounter(ShipCreationCounter::ShipSize::Five, fiveShipCountI, window, &selectedShip);
	selectShip(BattleField::ShipSize::Five);
	
	twoShipCounter->setPos(counterPosX, counterPosY);
	twoShipCounter->setSize(counterRectSize);
	threeShipCounter->setPos(counterPosX, counterPosY + counterOffset + counterRectSize);
	threeShipCounter->setSize(counterRectSize);
	fourShipCounter->setPos(counterPosX, counterPosY + (counterOffset + counterRectSize) * 2);
	fourShipCounter->setSize(counterRectSize);
	fiveShipCounter->setPos(counterPosX, counterPosY + (counterOffset + counterRectSize) * 3);
	fiveShipCounter->setSize(counterRectSize);
	
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
	
	if (twoShipCounter->isMouseOver())
		selectShip(BattleField::ShipSize::Two);
	if (threeShipCounter->isMouseOver())
		selectShip(BattleField::ShipSize::Three);
	if (fourShipCounter->isMouseOver())
		selectShip(BattleField::ShipSize::Four);
	if (fiveShipCounter->isMouseOver())
		selectShip(BattleField::ShipSize::Five);
	
	
}

void PlaceShips::selectShip(BattleField::ShipSize shipSize){
	twoShipCounter->deselect();
	threeShipCounter->deselect();
	fourShipCounter->deselect();
	fiveShipCounter->deselect();
	
	if (shipSize == BattleField::ShipSize::Two){
		battleField->setSelectedShipSize(BattleField::ShipSize::Two);
		twoShipCounter->select();
	}
	if (shipSize == BattleField::ShipSize::Three){
		battleField->setSelectedShipSize(BattleField::ShipSize::Three);
		threeShipCounter->select();
	}
	if (shipSize == BattleField::ShipSize::Four){
		battleField->setSelectedShipSize(BattleField::ShipSize::Four);
		fourShipCounter->select();
	}
	if (shipSize == BattleField::ShipSize::Five){
		battleField->setSelectedShipSize(BattleField::ShipSize::Five);
		fiveShipCounter->select();
	}
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
	battleField->draw();
	twoShipCounter->draw();
	threeShipCounter->draw();
	fourShipCounter->draw();
	fiveShipCounter->draw();
	
}