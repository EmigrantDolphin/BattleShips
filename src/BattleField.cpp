#include "BattleField.h"


BattleField::BattleField(sf::RenderWindow *window){
	this->window = window;
	selectedRectPos.x = -1;
	selectedRectPos.y = -1;
	createField();
}

void BattleField::createField(){
	fieldBounds.setSize(sf::Vector2f((RectSize+(RectThickness*2)) * FieldWidth,  (RectSize+(RectThickness*2)) * FieldHeight));
	fieldBounds.setOutlineThickness(RectThickness);
	fieldBounds.setOutlineColor(sf::Color::Black);
	fieldBounds.setPosition(posX-RectThickness, posY-RectThickness);
	
	for (int i = 0; i < FieldHeight; i++)
		for (int j = 0; j < FieldWidth; j++){
			fieldArr[i][j].setSize(sf::Vector2f(RectSize, RectSize));
			fieldArr[i][j].setOutlineThickness(RectThickness);
			fieldArr[i][j].setFillColor(sf::Color::White);
			fieldArr[i][j].setOutlineColor(sf::Color::Black);
			fieldArr[i][j].setPosition(j*RectSize + posX + j*RectThickness*2, i*RectSize + posY + i*RectThickness*2);
		}
}

void BattleField::draw(){
	for (int i = 0; i < FieldHeight; i++)
		for (int j = 0; j < FieldWidth; j++){
			//if [cell state] then depending on cell state
			if (fieldArr[i][j].state == RectShapeEnh::State::Alive)
				fieldArr[i][j].setFillColor(sf::Color(222, 184, 135));
			if (fieldArr[i][j].state == RectShapeEnh::State::Water)
				fieldArr[i][j].setFillColor(sf::Color::White);
		}
	
	selectRect();
	onMouseHover();
	
	window->draw(fieldBounds);
	for (int i = 0; i < FieldHeight; i++)
		for (int j = 0; j < FieldWidth; j++){
			window->draw(fieldArr[i][j]);
		}
		
}

float BattleField::getWidthHeight(){
	return (RectSize+RectThickness*2) * FieldWidth; 
}

void BattleField::setPos(float x, float y){
	posX = x;
	posY = y;
	//refreshes positions
	createField();
}
void BattleField::setEditState(EditState state){
	editState = state;
}

void BattleField::selectRect(){
	sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(*window);
	for (int i = 0; i < FieldHeight; i++)
		for (int j = 0; j < FieldWidth; j++){
			if (fieldArr[i][j].getGlobalBounds().contains(mousePos)){
				selectedRectPos.y = i;
				selectedRectPos.x = j;
				return;
			}
			
		}
	selectedRectPos.y = -1;
	selectedRectPos.x = -1;
}

void BattleField::onMouseHover(){	
	if (selectedRectPos.x != -1)
		switch(editState){
			case EditState::None :		fieldArr[selectedRectPos.y][selectedRectPos.x].setFillColor(sf::Color::Black);
									break;
			case EditState::Vertical :	hoverShipV();
									break;
			case EditState::Horizontal:	hoverShipH();
									break;
			case EditState::Erase :		fieldArr[selectedRectPos.y][selectedRectPos.x].setFillColor(sf::Color::Red);
		}
		
	
}

void BattleField::hoverShipH(){
	if (!doesHorizFit())
		return;
	for (int j = selectedRectPos.x; j < selectedRectPos.x+getSelectedShipSizeInt(); j++)
		fieldArr[selectedRectPos.y][j].setFillColor(sf::Color::Green);
}

void BattleField::hoverShipV(){
	if (!doesVertiFit())
		return;
	for (int i = selectedRectPos.y; i < selectedRectPos.y+getSelectedShipSizeInt(); i++)
		fieldArr[i][selectedRectPos.x].setFillColor(sf::Color::Green);
}

bool BattleField::doesHorizFit(){
	if (selectedRectPos.x == -1)
		return false;
	if (selectedRectPos.x+getSelectedShipSizeInt() > FieldWidth)
		return false;
	return true;
}

bool BattleField::doesVertiFit(){
	if (selectedRectPos.x == -1)
		return false;
	if (selectedRectPos.y+getSelectedShipSizeInt() > FieldHeight)
		return false;
	return true;
}
//shipSize is enum of {two three four five} = {0 1 2 3}
int BattleField::getSelectedShipSizeInt(){
	return selectedShipSize + 2;
}
void BattleField::setSelectedShipSize(ShipSize size){
	selectedShipSize = size;
}

BattleField::ShipSize BattleField::getSelectedShipSize(){
	return selectedShipSize;
}

BattleField::ShipSize BattleField::getLastDeletedShipSize(){
	return lastErasedShipSize;
}

bool BattleField::isNoOneAroundH(){
	if (!doesHorizFit())
		return false;
	sf::Vector2i topLeft;
	sf::Vector2i bottomRight;
	if (selectedRectPos.y - 1 >= 0)
		topLeft.y = selectedRectPos.y - 1;
	else
		topLeft.y = selectedRectPos.y;
	
	if (selectedRectPos.x -1 >= 0)
		topLeft.x = selectedRectPos.x -1;
	else
		topLeft.x = selectedRectPos.x;
	
	if (selectedRectPos.y + 1 < FieldHeight)
		bottomRight.y = selectedRectPos.y + 1;
	else
		bottomRight.y = selectedRectPos.y;
	
	if (selectedRectPos.x + getSelectedShipSizeInt() < FieldWidth)
		bottomRight.x = selectedRectPos.x + getSelectedShipSizeInt() ;
	else
		bottomRight.x = selectedRectPos.x + getSelectedShipSizeInt()-1;
	//fieldArr[topLeft.y][topLeft.x].setFillColor(sf::Color::Black);
	//fieldArr[bottomRight.y][bottomRight.x].setFillColor(sf::Color::Black);
	for (int i = topLeft.y; i <= bottomRight.y; i++)
		for (int j = topLeft.x; j <= bottomRight.x; j++)
			if (fieldArr[i][j].state != RectShapeEnh::State::Water)
				return false;
	return true;
}

bool BattleField::isNoOneAroundV(){
	if (!doesVertiFit())
		return false;
	sf::Vector2i topLeft;
	sf::Vector2i bottomRight;
	
	if (selectedRectPos.y - 1 >= 0)
		topLeft.y = selectedRectPos.y -1;
	else
		topLeft.y = selectedRectPos.y;
	
	if (selectedRectPos.x - 1 >= 0)
		topLeft.x = selectedRectPos.x -1;
	else
		topLeft.x = selectedRectPos.x;
	
	if (selectedRectPos.y + getSelectedShipSizeInt() < FieldHeight)
		bottomRight.y = selectedRectPos.y + getSelectedShipSizeInt();
	else
		bottomRight.y = selectedRectPos.y + getSelectedShipSizeInt() -1;
	
	if (selectedRectPos.x + 1 < FieldWidth)
		bottomRight.x = selectedRectPos.x + 1;
	else
		bottomRight.x = selectedRectPos.x;
	//fieldArr[topLeft.y][topLeft.x].setFillColor(sf::Color::Black);
	//fieldArr[bottomRight.y][bottomRight.x].setFillColor(sf::Color::Black);
	for (int i = topLeft.y; i <= bottomRight.y; i++)
		for (int j = topLeft.x; j <= bottomRight.x; j++)
			if (fieldArr[i][j].state != RectShapeEnh::State::Water)
				return false;
			
	return true;
}

int BattleField::eraseShip(int x, int y){
	int kills = 0;
	if (x < 0 || x >= FieldWidth || y < 0 || y >=FieldHeight)
		return 0;
	if (fieldArr[y][x].state == RectShapeEnh::State::Water)
		return 0;
	fieldArr[y][x].state = RectShapeEnh::State::Water;
	kills++;
	
	kills += eraseShip(x+1, y);
	kills += eraseShip(x-1, y);
	kills += eraseShip(x, y+1);
	kills += eraseShip(x, y-1);
	return kills;
}


bool BattleField::deleteShip(){
	if (editState == EditState::Erase && fieldArr[selectedRectPos.y][selectedRectPos.x].state == RectShapeEnh::State::Alive){
		int size = eraseShip(selectedRectPos.x, selectedRectPos.y);
		if (size == 2)
			lastErasedShipSize = ShipSize::Two;
		if (size == 3)
			lastErasedShipSize = ShipSize::Three;
		if (size == 4)
			lastErasedShipSize = ShipSize::Four;
		if (size == 5)
			lastErasedShipSize = ShipSize::Five;
		return true;
	}
	return false;
}

bool BattleField::placeShip(){
	if (editState == EditState::Horizontal && isNoOneAroundH()){
		for (int i = selectedRectPos.x; i < selectedRectPos.x + getSelectedShipSizeInt(); i++)
			fieldArr[selectedRectPos.y][i].state = RectShapeEnh::State::Alive;
		return true;
	}
	if (editState == EditState::Vertical && isNoOneAroundV()){
		for (int i = selectedRectPos.y; i < selectedRectPos.y + getSelectedShipSizeInt(); i++)
			fieldArr[i][selectedRectPos.x].state = RectShapeEnh::State::Alive;
		return true;
	}
	
	return false;
}

