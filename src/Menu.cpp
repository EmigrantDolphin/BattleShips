#include "Menu.h"


Menu::Menu(){
	Menu::setText();
}

void Menu::setText(){
	int centerX = GameMaster::windowSize.x / 2;
	int initialY = GameMaster::windowSize.y / 4;
	int textOffset = 100;	
	int textSize = 30;
	font.loadFromFile("fonts/arial.ttf");
	

	textPvP.setString("Player vs Player");
	textPvP.setFillColor(sf::Color::Green);
	textPvP.setFont(font);
	textPvP.setCharacterSize(textSize);
	textPvP.setPosition(centerX - (textPvP.getLocalBounds().width / 2), initialY);
	
	textPvC.setString("Player vs Computer");
	textPvC.setFillColor(sf::Color::Green);
	textPvC.setFont(font);
	textPvC.setCharacterSize(textSize);
	textPvC.setPosition(centerX - (textPvC.getLocalBounds().width / 2) , initialY + textOffset);
	
	textExit.setString("Exit");
	textExit.setFillColor(sf::Color::Green);
	textExit.setFont(font);
	textExit.setCharacterSize(textSize);
	textExit.setPosition(centerX - (textExit.getLocalBounds().width / 2), initialY + 2*textOffset);
}




void Menu::actions(){
	sf::Vector2f mousePos = GameMaster::mousePosition;
	
	if (textPvP.getGlobalBounds().contains(mousePos)){
		textPvP.setFillColor(sf::Color::Black);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			pvp = new PlayerVsPlayer();
			GameMaster::state = GameMaster::State::PvP;
		}
	}
	else
		textPvP.setFillColor(sf::Color::Green);
	
	if (textPvC.getGlobalBounds().contains(mousePos)){
		textPvC.setFillColor(sf::Color::Black);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			pvc = new PlayerVsComputer();
			GameMaster::state = GameMaster::State::PvC;
		}
	}
	else
		textPvC.setFillColor(sf::Color::Green);
	
	if (textExit.getGlobalBounds().contains(mousePos)){
		textExit.setFillColor(sf::Color::Black);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			GameMaster::state = GameMaster::State::Exit;
	}
	else
		textExit.setFillColor(sf::Color::Green);
}

void Menu::drawMenu(sf::RenderWindow &window){
	actions();
	window.draw(textPvC);
	window.draw(textExit);
	window.draw(textPvP);
}

void Menu::draw(sf::RenderWindow &window){
	switch (GameMaster::state){

		case GameMaster::State::PvP :	pvp->draw(window);
										break;
		case GameMaster::State::Menu :	drawMenu(window);
										break;
		case GameMaster::State::PvC :	pvc->draw(window);
										break;

	}
	
}


