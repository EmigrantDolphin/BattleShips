#include "BattleField.h"


BattleField::BattleField(sf::RenderWindow *window){
	this->window = window;
	createField();
}

void BattleField::createField(){
	
	for (int i = 0; i < FieldHeight; i++)
		for (int j = 0; j < FieldWidth; j++){
			fieldArr[i][j].setSize(sf::Vector2f(RectSize, RectSize));
			fieldArr[i][j].setOutlineThickness(RectThickness);
			fieldArr[i][j].setFillColor(sf::Color::White);
			fieldArr[i][j].setOutlineColor(sf::Color::Black);
			fieldArr[i][j].setPosition(j*RectSize + posX, i*RectSize + posY);
		}
}

void BattleField::draw(){
	for (int i = 0; i < FieldHeight; i++)
		for (int j = 0; j < FieldWidth; j++){
			window->draw(fieldArr[i][j]);
		}
}