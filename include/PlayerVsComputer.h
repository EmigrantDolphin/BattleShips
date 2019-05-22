
#include <SFML/Graphics.hpp>
#include "GameMaster.h"
#include "BattleField.h"
#include "IDrawable.h"
#include "IClickable.h"
#include "PlaceShips.h"
#include "PlaceShipsAuto.h"
#include "Button.h"
#include "RectShapeEnh.h"
#include <iostream>

class PlayerVsComputer : public IDrawable, public IClickable {
	enum State{Setup, Playing};
private:
	State state;
	BattleField *player, *computer;
	PlaceShips *placeShips;
	PlaceShipsAuto *placeShipsAuto;
	Button *exitButton;

	bool setupDone;
	void onSetupDone();
	
	bool isPlayerTurn;
	bool gameEnded;
	
	std::vector<sf::Vector2i> computerShotPos;
	std::vector<sf::Vector2i> poolOfCoords;
	std::vector<RectShapeEnh::State> computerShotState;
	sf::Vector2i computerTargetCoord;
	sf::Clock clock;
	int computerShotsFired;
	int dirInt;
	int distance;
	void computerChooseWhereToShoot();
	int findInPoolOfCoords(int, int);
	bool isComputerTargetDead();
	void onDeath();
public:
	PlayerVsComputer();
	~PlayerVsComputer();
	
	void draw(sf::RenderWindow &);
	void onMouseClick();
};