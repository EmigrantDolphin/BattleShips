#include "ShipCreationCounter.h"

ShipCreationCounter::ShipCreationCounter(int x, int y, ShipCreationCounter::ShipSize shipSize, int shipsLeft, sf::RenderWindow *window){
	this->window = window;
	this->shipSize = shipSize;
	rect = new sf::RectangleShape[shipSize+2];
	posX = x;
	posY = y;
	font.loadFromFile("fonts/arial.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(20);
	text.setPosition(posX + getShipWidth() + 5, posY);
	text.setString("x "+std::to_string(shipsLeft));
	
	for (int i = 0; i < shipSize+2; i++){
		rect[i].setSize(sf::Vector2f(rectSize, rectSize));
		rect[i].setOutlineThickness(rectThickness);
		rect[i].setOutlineColor(sf::Color::Black);
		rect[i].setPosition(posX + (i * rectSize), posY);
	}
}


void ShipCreationCounter::draw(){
	for (int i = 0; i < shipSize+2; i++)
		window->draw(rect[i]);
	window->draw(text);
}
void ShipCreationCounter::setShipsLeft(int shipsLeft){
	text.setString("x "+std::to_string(shipsLeft));
}
float ShipCreationCounter::getShipWidth(){
	return rectSize * (shipSize+2);
}

float ShipCreationCounter::getRectHeight(){
	return rectSize;
}