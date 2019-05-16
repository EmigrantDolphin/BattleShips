#include <SFML/Graphics.hpp>
#include "GameMaster.h"

class Menu{
private:
	sf::Text textPvP, textPvC, textExit;
	sf::Font font;
	void setText();
public:
	Menu();
	void draw(sf::RenderWindow &);
	void actions();
	
};