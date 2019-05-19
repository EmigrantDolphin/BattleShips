#ifndef _RECTSHAPEENHH_
#define _RECTSHAPEENHH_

#include <SFML/Graphics.hpp>

class RectShapeEnh : public sf::RectangleShape{
public:
	enum State {Alive, Hit, Dead, Water, Bubble};
	enum ShipVisibility {On, Off};
	bool visited = false; // bad practice, cuz this is only used for recursive checking if whole ship is hit
	State state = State::Water;
	ShipVisibility shipVisibility = ShipVisibility::On;
};

#endif