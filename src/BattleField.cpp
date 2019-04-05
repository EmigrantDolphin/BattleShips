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
	onMouseClick();
	onKeyPress();
	
	window->draw(fieldBounds);
	for (int i = 0; i < FieldHeight; i++)
		for (int j = 0; j < FieldWidth; j++){
			window->draw(fieldArr[i][j]);
		}
		
}

void BattleField::setPos(float x, float y){
	posX = x;
	posY = y;
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
	for (int j = selectedRectPos.x; j < selectedRectPos.x+getSelectedShipSize(); j++)
		fieldArr[selectedRectPos.y][j].setFillColor(sf::Color::Green);
}

void BattleField::hoverShipV(){
	if (!doesVertiFit())
		return;
	for (int i = selectedRectPos.y; i < selectedRectPos.y+getSelectedShipSize(); i++)
		fieldArr[i][selectedRectPos.x].setFillColor(sf::Color::Green);
}

bool BattleField::doesHorizFit(){
	if (selectedRectPos.x == -1)
		return false;
	if (selectedRectPos.x+getSelectedShipSize() > FieldWidth)
		return false;
	return true;
}

bool BattleField::doesVertiFit(){
	if (selectedRectPos.x == -1)
		return false;
	if (selectedRectPos.y+getSelectedShipSize() > FieldHeight)
		return false;
	return true;
}
//shipSize is enum of {two three four five} = {0 1 2 3}
int BattleField::getSelectedShipSize(){
	return selectedShipSize + 2;
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
	
	if (selectedRectPos.x + getSelectedShipSize() < FieldWidth)
		bottomRight.x = selectedRectPos.x + getSelectedShipSize() ;
	else
		bottomRight.x = selectedRectPos.x + getSelectedShipSize()-1;
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
	
	if (selectedRectPos.y + getSelectedShipSize() < FieldHeight)
		bottomRight.y = selectedRectPos.y + getSelectedShipSize();
	else
		bottomRight.y = selectedRectPos.y + getSelectedShipSize() -1;
	
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

void BattleField::onMouseClick(){
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return;
	
	if (editState == EditState::Horizontal && isNoOneAroundH()){
		for (int i = selectedRectPos.x; i < selectedRectPos.x + getSelectedShipSize(); i++)
			fieldArr[selectedRectPos.y][i].state = RectShapeEnh::State::Alive;
	}
	if (editState == EditState::Vertical && isNoOneAroundV())
		for (int i = selectedRectPos.y; i < selectedRectPos.y + getSelectedShipSize(); i++)
			fieldArr[i][selectedRectPos.x].state = RectShapeEnh::State::Alive;

	if (editState == EditState::Erase && fieldArr[selectedRectPos.y][selectedRectPos.x].state == RectShapeEnh::State::Alive)
		eraseShip(selectedRectPos.x, selectedRectPos.y);
}

void BattleField::onKeyPress(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		editState = EditState::Horizontal;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		editState = EditState::Vertical;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		editState = EditState::Erase;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		selectedShipSize = ShipSize::Two;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		selectedShipSize = ShipSize::Three;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		selectedShipSize = ShipSize::Four;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		selectedShipSize = ShipSize::Five;
}
