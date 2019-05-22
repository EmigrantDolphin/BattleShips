#include "PlaceShips.h"

PlaceShips::PlaceShips(BattleField *battleField, bool *isSetup){
	this->battleField = battleField;
	this->isSetup = isSetup;
	init();
}

void PlaceShips::init(){
	float x = GameMaster::windowSize.x / 2 - battleField->getWidthHeight() /2;
	float y = (GameMaster::windowSize.y - battleField->getWidthHeight()) / 2;
	battleField->setPos(x, y);
	this->selectedShip = battleField->getSelectedShipRef();
	
	// could probs couple counters in another class and then call class here, but I need to hurry...
	this->twoShipCounter = new ShipCreationCounter(BattleField::ShipSize::Two, twoShipCountI, selectedShip);
	this->threeShipCounter = new ShipCreationCounter(BattleField::ShipSize::Three, threeShipCountI, selectedShip);
	this->fourShipCounter = new ShipCreationCounter(BattleField::ShipSize::Four, fourShipCountI, selectedShip);
	this->fiveShipCounter = new ShipCreationCounter(BattleField::ShipSize::Five, fiveShipCountI, selectedShip);
	
	twoShipCounter->setPos(counterPosX, counterPosY);
	twoShipCounter->setSize(counterRectSize);
	threeShipCounter->setPos(counterPosX, counterPosY + counterOffset + counterRectSize);
	threeShipCounter->setSize(counterRectSize);
	fourShipCounter->setPos(counterPosX, counterPosY + (counterOffset + counterRectSize) * 2);
	fourShipCounter->setSize(counterRectSize);
	fiveShipCounter->setPos(counterPosX, counterPosY + (counterOffset + counterRectSize) * 3);
	fiveShipCounter->setSize(counterRectSize);
	
	drawables.push_back(twoShipCounter);
	drawables.push_back(threeShipCounter);
	drawables.push_back(fourShipCounter);
	drawables.push_back(fiveShipCounter);
	
	clickables.push_back(twoShipCounter);
	clickables.push_back(threeShipCounter);
	clickables.push_back(fourShipCounter);
	clickables.push_back(fiveShipCounter);
	
	//auto HFunc = [&](void){ battleField->setEditState(BattleField::EditState::Horizontal); };
	HButton = new Button([&](void){ battleField->setEditState(BattleField::EditState::Horizontal); });
	HButton->setText("H");
	HButton->setPosition(counterPosX, counterPosY + (counterOffset + counterRectSize) * 4);
	
	VButton = new Button([&](void){ battleField->setEditState(BattleField::EditState::Vertical); });
	VButton->setText("V");
	VButton->setWidth(HButton->getWidth());
	VButton->setPosition(counterPosX + HButton->getWidth()+buttonOffset, counterPosY + (counterOffset + counterRectSize) * 4);
	
	
	EButton = new Button([&](void){ battleField->setEditState(BattleField::EditState::Erase); });
	EButton->setText("E");
	EButton->setWidth(HButton->getWidth());
	EButton->setPosition(counterPosX + VButton->getWidth()*2+buttonOffset*2, counterPosY + (counterOffset + counterRectSize) * 4);
	
	VButton->select();
	
	drawables.push_back(HButton);
	drawables.push_back(VButton);
	drawables.push_back(EButton);
	
	clickables.push_back(HButton);
	clickables.push_back(VButton);
	clickables.push_back(EButton);
	
	// exit button
	
	exitButton = new Button([&](void){ 
		if (twoShipCountI + threeShipCountI + fourShipCountI + fiveShipCountI == 0)
			(*isSetup) = true; 
	});
	exitButton->setText("Done");
	exitButton->setPosition(counterPosX, counterPosY + (counterOffset + counterRectSize) * 5);
	drawables.push_back(exitButton);
	clickables.push_back(exitButton);
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
	
	for (int i = 0; i < clickables.size(); i++)
		clickables[i]->onMouseClick();
	
	
	if (battleField->getEditState() == BattleField::EditState::Horizontal)
		HButton->select();
	else
		HButton->deselect();
	
	if (battleField->getEditState() == BattleField::EditState::Vertical)
		VButton->select();
	else
		VButton->deselect();
	
	if (battleField->getEditState() == BattleField::EditState::Erase)
		EButton->select();
	else
		EButton->deselect();
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

void PlaceShips::draw(sf::RenderWindow &window){
	onKeyPress();
	onMouseClick();
	
	for (int i = 0; i < drawables.size(); i++)
		drawables[i]->draw(window);
	battleField->draw(window);
}

PlaceShips::~PlaceShips(){
	delete HButton;
	delete VButton;
	delete EButton;
	delete exitButton;
}