#include "ShipCreationCounter.h"

ShipCreationCounter::ShipCreationCounter(ShipCreationCounter::ShipSize shipSize, int shipsLeft, sf::RenderWindow *window){
	this->window = window;
	this->shipSize = shipSize;
	rect = new sf::RectangleShape[shipSize+2];
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

void ShipCreationCounter::refresh(){
	for (int i = 0; i < shipSize+2; i++){
		rect[i].setSize(sf::Vector2f(rectSize, rectSize));
		rect[i].setPosition(posX + (i * rectSize), posY);
	}
	text.setPosition(posX + getShipWidth() + 5, posY);
}


void ShipCreationCounter::draw(){
	for (int i = 0; i < shipSize+2; i++)
		window->draw(rect[i]);
	window->draw(text);
}
void ShipCreationCounter::select(){
		for (int i = 0; i < shipSize+2; i++)
			rect[i].setFillColor(sf::Color::Green);
}
void ShipCreationCounter::deselect(){
	for (int i = 0; i < shipSize+2; i++)
			rect[i].setFillColor(sf::Color::White);
}
bool ShipCreationCounter::isMouseOver(){
	sf::Vector2i mousePos = (sf::Vector2i)sf::Mouse::getPosition(*window);
	sf::IntRect ship(posX, posY, getShipWidth(), rectSize); 
	if (ship.contains(mousePos))
		return true;
	return false;
}

//SET GET
void ShipCreationCounter::setShipsLeft(int shipsLeft){
	text.setString("x "+std::to_string(shipsLeft));
}
float ShipCreationCounter::getShipWidth(){
	return rectSize * (shipSize+2);
}

float ShipCreationCounter::getWidth(){
	return getShipWidth();
}
float ShipCreationCounter::getHeight(){
	return rectSize;
}

void ShipCreationCounter::setPos(float x, float y){
	posX = x;
	posY = y;
	refresh();
}
void ShipCreationCounter::setSize(float size){
	rectSize = size;
	refresh();
}