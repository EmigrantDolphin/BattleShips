#include "PlayerVsPlayer.h"

PlayerVsPlayer::PlayerVsPlayer(sf::RenderWindow *window){
	this->window = window;
	this->player1 = new BattleField(this->window);
	this->player2 = new BattleField(this->window);
	this->placeShips = new PlaceShips(window, player1);
}

void PlayerVsPlayer::draw(){
	placeShips->draw();
}