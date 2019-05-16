#include "GameMaster.h"
GameMaster::State GameMaster::state = GameMaster::State::Menu;
sf::Vector2f GameMaster::windowSize = sf::Vector2f(0,0);
sf::Vector2f GameMaster::mousePosition = sf::Vector2f(0,0);