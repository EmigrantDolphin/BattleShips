#include <SFML/Graphics.hpp>
#include "GameMaster.h"

class Menu{
private:
	sf::RenderWindow *windo;
	sf::Text textPvP, textPvC, textExit;
	sf::Font font;
	void setText();
public:
	Menu(sf::RenderWindow *);
	void draw();
	void actions();
	
};