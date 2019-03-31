#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "GameMaster.h"

#include <iostream>


sf::RenderWindow window(sf::VideoMode(1000, 500), "Battle Ships");
Menu menuClass(&window);

int main(){
    

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
			window.close();
		}

		window.clear(sf::Color::White);	
		
		switch (GameMaster::state){
			case GameMaster::State::Menu :  menuClass.actions();
											menuClass.draw();
											break;
		}

		window.display();
	}


    return 0;
}
