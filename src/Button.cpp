#include "Button.h"


Button::Button(void (*callback)()) : textSize(30), borderThickness(1){
	this->callback = callback;
	font.loadFromFile("fonts/arial.ttf");
	text.setFont(font);
	text.setCharacterSize(textSize);
	text.setFillColor(sf::Color::Black);
	
	border.setFillColor(sf::Color::White);
	border.setOutlineColor(sf::Color::Black);
	border.setOutlineThickness(borderThickness);
}


void Button::draw(){
	
}

void Button::onMouseClick(){
	
}

void Button::setPosition(float x, float y){
	text.setPosition(x+1, y+1);
	border.setPosition(x, y);
}

void Button::setText(std::string textS){
	text.setString(textS);
	border.setSize(sf::Vector2f(text.getGlobalBounds().width + 2, text.getGlobalBounds().height + 2));
}