#ifndef _PLAYERVSPLAYERH_
#define _PLAYERVSPLAYERH_

#include <SFML/Graphics.hpp>
#include "BattleField.h"
#include "PlaceShips.h"
#include "IDrawable.h"

class PlayerVsPlayer : public IDrawable{
public:
	enum State{EditingP1, EditingP2, Playing};
private:
	State state = State::EditingP1;
	BattleField *player1;
	BattleField *player2;
	PlaceShips *placeShips;

	
	
public:
	PlayerVsPlayer();
	
	void draw(sf::RenderWindow &);

};

#endif