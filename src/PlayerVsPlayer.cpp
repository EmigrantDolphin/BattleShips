#include "PlayerVsPlayer.h"

PlayerVsPlayer::PlayerVsPlayer(){
	this->player1 = new BattleField();
	this->player2 = new BattleField();
	this->placeShips = new PlaceShips(player1);
}

void PlayerVsPlayer::draw(sf::RenderWindow &window){
	placeShips->draw(window);
}