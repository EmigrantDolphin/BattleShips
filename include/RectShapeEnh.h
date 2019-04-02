#include <SFML/Graphics.hpp>

class RectShapeEnh : public sf::RectangleShape{
public:
	enum State {Alive, Hit, Dead, Water, Bubble};
	enum ShipVisibility {On, Off};
	State state = State::Water;
	ShipVisibility shipVisibility = ShipVisibility::On;
};