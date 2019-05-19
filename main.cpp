#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "GameMaster.h"
#include "BattleField.h"
#include "PlayerVsPlayer.h"


#include <iostream>


sf::RenderWindow window(sf::VideoMode(1000, 500), "Battle Ships");

int main(){
	GameMaster::state = GameMaster::State::Menu;
	GameMaster::windowSize = (sf::Vector2f)window.getSize();
	Menu menuClass;
	
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
			window.close();
		}

		window.clear(sf::Color::White);	
		GameMaster::mousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
		
		menuClass.draw(window);
		
		if (GameMaster::state == GameMaster::State::Exit)
			window.close();
		
		window.display();
	}


    return 0;
}
