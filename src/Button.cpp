#include "Button.h"


Button::Button(std::function<void (void)> f) : textSize(30), borderThickness(1){
	func = f;
	font.loadFromFile("fonts/arial.ttf");
	text.setFont(font);
	text.setCharacterSize(textSize);
	text.setFillColor(sf::Color::Black);
	
	border.setFillColor(sf::Color::White);
	border.setOutlineColor(sf::Color::Black);
	border.setOutlineThickness(borderThickness);
}


void Button::draw(sf::RenderWindow &window){
	window.draw(border);
	window.draw(text);
}

void Button::onMouseClick(){
	if (border.getGlobalBounds().contains(GameMaster::mousePosition)){
		func();
	}
}

void Button::select(){
	border.setFillColor(sf::Color::Green);
}
void Button::deselect(){
	border.setFillColor(sf::Color::White);
}
float Button::getWidth(){
	return border.getLocalBounds().width;
}
void Button::setWidth(float width){
	border.setSize(sf::Vector2f(width, border.getLocalBounds().height));
}

void Button::setPosition(float x, float y){
	text.setOrigin(text.getLocalBounds().left, text.getLocalBounds().top);
	text.setPosition(-1+x + (border.getLocalBounds().width - text.getLocalBounds().width) / 2, y+2);
	border.setPosition(x, y);
}

void Button::setText(std::string textS){
	text.setString(textS);
	border.setSize(sf::Vector2f(text.getGlobalBounds().width + 4, text.getGlobalBounds().height + 4));
}