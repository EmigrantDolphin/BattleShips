#include "BattleField.h"


BattleField::BattleField(sf::RenderWindow *window){
	this->window = window;
	createField();
}

void BattleField::createField(){
	fieldBounds.setSize(sf::Vector2f(RectSize * FieldWidth+2,  RectSize * FieldHeight+2));
	fieldBounds.setOutlineThickness(1);
	fieldBounds.setOutlineColor(sf::Color::Black);
	fieldBounds.setPosition(posX-1, posY-1);
	
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
	
	for (int i = 0; i < FieldHeight; i++)
		for (int j = 0; j < FieldWidth; j++){
			if (fieldArr[i][j].getGlobalBounds().contains(mousePos))
				fieldArr[i][j].setFillColor(sf::Color::Red);
			else
				fieldArr[i][j].setFillColor(sf::Color::White);
		}
	
}