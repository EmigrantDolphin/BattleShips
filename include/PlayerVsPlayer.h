#ifndef _PLAYERVSPLAYERH_
#define _PLAYERVSPLAYERH_

#include <SFML/Graphics.hpp>
#include "GameMaster.h"
#include "BattleField.h"
#include "PlaceShips.h"
#include "IDrawable.h"
#include "RectShapeEnh.h"
#include "Button.h"
#include <iostream>

class PlayerVsPlayer : public IDrawable, public IClickable{
public:
	enum State{EditingP1, EditingP2, Playing};
private:
	State state = State::EditingP1;
	BattleField *player1;
	BattleField *player2;
	PlaceShips *placeShips;
	bool isPlayerSetup;
	bool isPlayerOneTurn;
	bool gameEnded;
	Button *exitButton;

	void setupPvP();
public:
	PlayerVsPlayer();
	~PlayerVsPlayer();
	void onMouseClick();
	void draw(sf::RenderWindow &);

};

#endif