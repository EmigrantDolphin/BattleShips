#include <SFML/Graphics.hpp>
#include "GameMaster.h"
#include "IDrawable.h"
#include "PlayerVsPlayer.h"
#include "PlayerVsComputer.h"

class Menu : public IDrawable{
private:
	sf::Text textPvP, textPvC, textExit;
	sf::Font font;
	
	PlayerVsPlayer *pvp;
	PlayerVsComputer *pvc;
	
	void actions();
	void setText();
public:
	Menu();
	void draw(sf::RenderWindow &);
	void drawMenu(sf::RenderWindow &);
	
};