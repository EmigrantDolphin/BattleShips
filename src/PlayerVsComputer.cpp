#include "PlayerVsComputer.h"

PlayerVsComputer::PlayerVsComputer() : setupDone(false), state(State::Setup), gameEnded(false), isPlayerTurn(true), 
									   computerShotsFired(0), dirInt(0), distance(0), computerTargetCoord(sf::Vector2i(-1, -1)){
	this->player = new BattleField("player");
	do{ // this is such bad practice that I might as well shoot myself. But I don't have time!!!!!
		this->computer = new BattleField("computer");
		this->placeShipsAuto = new PlaceShipsAuto(computer);
	}while(placeShipsAuto->getShipsLeft() != 0);
	this->placeShips = new PlaceShips(player, &setupDone);
	this->exitButton = new Button([&](void){ GameMaster::state = GameMaster::State::Menu; });
	exitButton->setText("exit");
	exitButton->setPosition((GameMaster::windowSize.x / 2)-(exitButton->getWidth() / 2), 10);
}


void PlayerVsComputer::draw(sf::RenderWindow &window){
	if (setupDone && state == State::Setup){
		state = State::Playing;
		onSetupDone();
	}
	else if (!setupDone){
		placeShips->draw(window);
	}else{
		onMouseClick();
		player->draw(window);
		computer->draw(window);
		if (gameEnded)
			exitButton->draw(window);
	}
	
}

void PlayerVsComputer::onMouseClick(){
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if (gameEnded)
			exitButton->onMouseClick();
	}
	
	if (player->getDeadShipCount() < player->getTotalShipCount() && computer->getDeadShipCount() < computer->getTotalShipCount()){
		if (isPlayerTurn){
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
				return;
			if (computer->hit() == RectShapeEnh::State::Water){
				isPlayerTurn = false;
				computer->setNameColor(sf::Color::Black);
				player->setNameColor(sf::Color::Red);
				clock.restart();
			}		
		}else{
			if (clock.getElapsedTime().asMilliseconds() > 500){
				computerChooseWhereToShoot();
				RectShapeEnh::State shotState = player->hit();
				computerShotState.push_back(shotState);
				if (shotState == RectShapeEnh::State::Water){
					isPlayerTurn = true;
					player->setNameColor(sf::Color::Black);
					computer->setNameColor(sf::Color::Red);
				}
				if (shotState == RectShapeEnh::State::Alive)
					clock.restart();
				
			}
		}
	}else{
		player->shipVisibility(true);
		computer->shipVisibility(true);
		gameEnded = true;
		player->setNameColor(sf::Color::Black);
		computer->setNameColor(sf::Color::Black);
		if (player->getDeadShipCount() == player->getTotalShipCount()){
			computer->setNameText("computer WON");
			computer->setNameColor(sf::Color::Green);
		}
		if (computer->getDeadShipCount() == computer->getTotalShipCount()){
			player->setNameText("player WON");
			player->setNameColor(sf::Color::Green);
		}
	}
}

void PlayerVsComputer::onSetupDone(){
	for (int i = 0; i < computer->getFieldHeight(); i++)
		for (int j = 0; j < computer->getFieldWidth(); j++)
			poolOfCoords.push_back(sf::Vector2i(j, i));
		
	player->setPos((GameMaster::windowSize.x / 2) - player->getWidthHeight() - 20, (GameMaster::windowSize.y / 2) - (player->getWidthHeight() / 2));
	computer->setPos(player->getPos().x + player->getWidthHeight() + 50, player->getPos().y);
	player->shipVisibility(false);
	computer->shipVisibility(false);
	computer->setNameColor(sf::Color::Red);
}

void PlayerVsComputer::computerChooseWhereToShoot(){
	int num, x, y;
	if (computerShotState.size() == 0){
		num = rand() % poolOfCoords.size();
		x = poolOfCoords[num].x;
		y = poolOfCoords[num].y;
		player->setSelectedRectPos(x, y);
		computerShotPos.push_back(poolOfCoords[num]);
		poolOfCoords.erase(poolOfCoords.begin()+num);
		return;
	}
	if (computerShotState[computerShotState.size()-1] == RectShapeEnh::State::Alive && computerTargetCoord.x == -1)
		computerTargetCoord = sf::Vector2i(computerShotPos[computerShotPos.size()-1]);
	
	if (isComputerTargetDead()){
		computerTargetCoord = sf::Vector2i(-1,-1);
		distance = 0;
		dirInt = 0;
	}
	
	if (!isComputerTargetDead() && computerShotState[computerShotState.size()-1] != RectShapeEnh::State::Alive && distance > 1){
		dirInt+=2;
		distance = 1;
	}else if (!isComputerTargetDead() && computerShotState[computerShotState.size()-1] != RectShapeEnh::State::Alive){
		dirInt++;
		distance = 1;
	}
	
	if (!isComputerTargetDead() && computerShotState[computerShotState.size()-1] == RectShapeEnh::State::Alive)
		distance++;
	
	if (computerTargetCoord.x == -1){ //if not alive
		num = rand() % poolOfCoords.size();
		x = poolOfCoords[num].x;
		y = poolOfCoords[num].y;
	}else{
		if (dirInt == 0){
			if (computerTargetCoord.x + distance < player->getFieldWidth() && findInPoolOfCoords(computerTargetCoord.x+distance, computerTargetCoord.y) != -1){
				x = computerTargetCoord.x + distance;
				y = computerTargetCoord.y;
			}else{
				dirInt++;
				distance = 1;
			}
		} 
		if (dirInt == 1){
			if (computerTargetCoord.y + distance < player->getFieldHeight() && findInPoolOfCoords(computerTargetCoord.x, computerTargetCoord.y+distance) != -1){
				x = computerTargetCoord.x;
				y = computerTargetCoord.y + distance;
			}else{
				dirInt++;
				distance = 1;
			}
		}
		if (dirInt == 2){
			if (computerTargetCoord.x - distance >= 0 && findInPoolOfCoords(computerTargetCoord.x-distance, computerTargetCoord.y) != -1){
				x = computerTargetCoord.x - distance;
				y = computerTargetCoord.y;
			}else{
				dirInt++;
				distance = 1;
			}
		}
		if (dirInt == 3){
			if (computerTargetCoord.y - distance >= 0 && findInPoolOfCoords(computerTargetCoord.x, computerTargetCoord.y-distance) != -1){
				x = computerTargetCoord.x;
				y = computerTargetCoord.y - distance;
			}else{
				dirInt=0;
				distance = 1;
			}
		}
		num = findInPoolOfCoords(x, y);
	}
	
	player->setSelectedRectPos(x, y);
	//computerShotPos.push_back(sf::Vector2i(x, y));
	if (num != -1){
		computerShotPos.push_back(poolOfCoords[num]);
		poolOfCoords.erase(poolOfCoords.begin()+num);	
	}
}

int PlayerVsComputer::findInPoolOfCoords(int x, int y){
	for (int i = 0; i < poolOfCoords.size(); i++)
		if (poolOfCoords[i].x == x && poolOfCoords[i].y == y)
			return i;
	return -1;
}

bool PlayerVsComputer::isComputerTargetDead(){
	if (computerTargetCoord.x == -1)
		return true;
	player->setSelectedRectPos(computerTargetCoord.x, computerTargetCoord.y);
	if (player->hit() == RectShapeEnh::State::Dead){
		onDeath();
		return true;
	}
	return false;
}

void PlayerVsComputer::onDeath(){
	for (int i = 0; i < player->getFieldHeight(); i++)
		for (int j = 0; j < player->getFieldWidth(); j++){
			if (player->getFieldCell(i,j).state == RectShapeEnh::State::Dead){
				if (findInPoolOfCoords(j+1, i) != -1)
					poolOfCoords.erase(poolOfCoords.begin() + findInPoolOfCoords(j+1, i));
				if (findInPoolOfCoords(j-1, i) != -1)
					poolOfCoords.erase(poolOfCoords.begin() + findInPoolOfCoords(j-1, i));
				if (findInPoolOfCoords(j, i+1) != -1)
					poolOfCoords.erase(poolOfCoords.begin() + findInPoolOfCoords(j, i+1));
				if (findInPoolOfCoords(j, i-1) != -1)
					poolOfCoords.erase(poolOfCoords.begin() + findInPoolOfCoords(j, i-1));
				if (findInPoolOfCoords(j+1, i+1) != -1)
					poolOfCoords.erase(poolOfCoords.begin() + findInPoolOfCoords(j+1, i+1));
				if (findInPoolOfCoords(j+1, i-1) != -1)
					poolOfCoords.erase(poolOfCoords.begin() + findInPoolOfCoords(j+1, i-1));
				if (findInPoolOfCoords(j-1, i-1) != -1)
					poolOfCoords.erase(poolOfCoords.begin() + findInPoolOfCoords(j-1, i-1));
				if (findInPoolOfCoords(j-1, i+1) != -1)
					poolOfCoords.erase(poolOfCoords.begin() + findInPoolOfCoords(j-1, i+1));
			}
		}
}

PlayerVsComputer::~PlayerVsComputer(){
	delete exitButton;
	delete placeShips;
	delete player;
	delete computer;
}
	
