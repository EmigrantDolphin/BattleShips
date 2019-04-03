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
			fieldArr[i][j].setFillColor(sf::Color::White);
		}
	
	selectRect();
	onMouseHover();
	onMouseClick();
	
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
			case EditState::Vertical :		hoverShipV();
									break;
			case EditState::Horizontal:	hoverShipH();
									break;
		}
		
	
}
//shipSize is enum of {one two three four} = {0 1 2 3}
void BattleField::hoverShipH(){
	if (selectedRectPos.x+shipSize+1 > FieldWidth)
		return;
	for (int j = selectedRectPos.x; j < selectedRectPos.x+shipSize+1; j++)
		fieldArr[selectedRectPos.y][j].setFillColor(sf::Color::Green);
}

void BattleField::hoverShipV(){
	if (selectedRectPos.y+shipSize+1 > FieldHeight)
		return;
	for (int i = selectedRectPos.y; i < selectedRectPos.y+shipSize+1; i++)
		fieldArr[i][selectedRectPos.x].setFillColor(sf::Color::Green);
}

void BattleField::onMouseClick(){
	//save ship and ship caunter and stuff
}
