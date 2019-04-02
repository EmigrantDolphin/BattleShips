#include "BattleField.h"


BattleField::BattleField(sf::RenderWindow *window){
	this->window = window;
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

void BattleField::onMouseHover(){
	sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(*window);
	int selectedI = -1, selectedJ = -1;
	for (int i = 0; i < FieldHeight; i++)
		for (int j = 0; j < FieldWidth; j++){
			if (fieldArr[i][j].getGlobalBounds().contains(mousePos)){
				selectedI = i;
				selectedJ = j;
			}
			fieldArr[i][j].setFillColor(sf::Color::White);
			
		}
	
	if (selectedI != -1)
		switch(editState){
			case EditState::None :		fieldArr[selectedI][selectedJ].setFillColor(sf::Color::Black);
									break;
			case EditState::Vertical :		hoverShipV(selectedI, selectedJ);
									break;
			case EditState::Horizontal:	hoverShipH(selectedI, selectedJ);
									break;
		}
		
	
}
//shipSize is enum of {one two three four} = {0 1 2 3}
void BattleField::hoverShipH(int selectedI, int selectedJ){
	if (selectedJ+shipSize+1 > FieldWidth)
		return;
	for (int j = selectedJ; j < selectedJ+shipSize+1; j++)
		fieldArr[selectedI][j].setFillColor(sf::Color::Green);
}

void BattleField::hoverShipV(int selectedI, int selectedJ){
	if (selectedI+shipSize+1 > FieldHeight)
		return;
	for (int i = selectedI; i < selectedI+shipSize+1; i++)
		fieldArr[i][selectedJ].setFillColor(sf::Color::Green);
}

void BattleField::onMouseClick(){
	//save ship and ship caunter and stuff
}
