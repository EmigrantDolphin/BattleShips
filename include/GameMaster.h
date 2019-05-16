#ifndef _GAMEMASTERH_
#define _GAMEMASTERH_

#include <SFML/Graphics.hpp>

class GameMaster{
public:
	enum State{Menu, PvP, PvC, Exit};
	static State state;	
};

#endif