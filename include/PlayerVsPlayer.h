#ifndef _PLAYERVSPLAYERH_
#define _PLAYERVSPLAYERH_

#include <SFML/Graphics.hpp>
#include "BattleField.h"
#include "PlaceShips.h"

class PlayerVsPlayer{
public:
	enum State{EditingP1, EditingP2, Playing};
private:
	sf::RenderWindow *window;
	State state = State::EditingP1;
	BattleField *player1;
	BattleField *player2;
	PlaceShips *placeShips;

	
	
public:
	PlayerVsPlayer(sf::RenderWindow *);
	
	void draw();

};

#endif