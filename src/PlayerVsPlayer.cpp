#include "PlayerVsPlayer.h"

PlayerVsPlayer::PlayerVsPlayer() : isPlayerSetup(false), isPlayerOneTurn(true), gameEnded(false){
	this->player1 = new BattleField("player1");
	this->player2 = new BattleField("player2");
	this->placeShips = new PlaceShips(player1, &isPlayerSetup);
	
	exitButton = new Button([&](void){ GameMaster::state = GameMaster::State::Menu; });
	exitButton->setText("exit");
	exitButton->setPosition((GameMaster::windowSize.x / 2)-(exitButton->getWidth() / 2), 10);
}


void PlayerVsPlayer::draw(sf::RenderWindow &window){
	if (isPlayerSetup){
		if (state == PlayerVsPlayer::State::EditingP2)
			state = PlayerVsPlayer::State::Playing;
		if (state == PlayerVsPlayer::State::EditingP1)
			state = PlayerVsPlayer::State::EditingP2;
		isPlayerSetup = false;
		
		if (state == PlayerVsPlayer::State::EditingP2)
			placeShips = new PlaceShips(player2, &isPlayerSetup);
		if (state == PlayerVsPlayer::State::Playing)
			setupPvP();
	}
	
	if (state == PlayerVsPlayer::State::EditingP1 || state == PlayerVsPlayer::State::EditingP2)	
		placeShips->draw(window);
	if (state == PlayerVsPlayer::State::Playing){
		onMouseClick();
		player1->draw(window);
		player2->draw(window);
		if (gameEnded)
			exitButton->draw(window);
		
	}
	
}

void PlayerVsPlayer::setupPvP(){
	player1->setPos((GameMaster::windowSize.x / 2) - player1->getWidthHeight() - 20, (GameMaster::windowSize.y / 2) - (player1->getWidthHeight() / 2));
	player2->setPos(player1->getPos().x + player1->getWidthHeight() + 50, player2->getPos().y);
	player1->shipVisibility(false);
	player2->shipVisibility(false);
	player1->setNameColor(sf::Color::Red);
}

void PlayerVsPlayer::onMouseClick(){
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return;
	if (gameEnded)
		exitButton->onMouseClick();
	
	if (player1->getDeadShipCount() < player1->getTotalShipCount() && player2->getDeadShipCount() < player2->getTotalShipCount()){
		if (isPlayerOneTurn){
			if (player1->hit() == RectShapeEnh::State::Water){
				isPlayerOneTurn = false;
				player1->setNameColor(sf::Color::Black);
				player2->setNameColor(sf::Color::Red);
			}
		}else{
			if (player2->hit() == RectShapeEnh::State::Water){
				isPlayerOneTurn = true;
				player2->setNameColor(sf::Color::Black);
				player1->setNameColor(sf::Color::Red);
			}
		}
	}else{
		player1->shipVisibility(true);
		player2->shipVisibility(true);
		gameEnded = true;
		player1->setNameColor(sf::Color::Black);
		player2->setNameColor(sf::Color::Black);
		if (player1->getDeadShipCount() == player1->getTotalShipCount()){
			player2->setNameText("player2 WON");
			player2->setNameColor(sf::Color::Green);
		}
		if (player2->getDeadShipCount() == player2->getTotalShipCount()){
			player1->setNameText("player1 WON");
			player1->setNameColor(sf::Color::Green);
		}
	}

}