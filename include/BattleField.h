#include <SFML/Graphics.hpp>
#include <RectShapeEnh.h>
class BattleField{
public:
	enum EditState {Horizontal, Vertical, None};
	enum ShipSize {One, Two, Three, Four};
private:
	sf::RenderWindow *window;
	EditState editState = EditState::Vertical;
	ShipSize shipSize = ShipSize::Three;
	
	float posX = 10, posY = 10;
	static const int FieldWidth = 10, FieldHeight = 10, RectSize = 30, RectThickness = 1;
	RectShapeEnh fieldArr[FieldWidth][FieldHeight];
	sf::RectangleShape fieldBounds; // to make edges same as inner lines
	
	void createField();
	void onMouseHover();
	void hoverShipH(int, int); //used in onMouseHover to draw hovering ship, not yet placed
	void hoverShipV(int, int);
	void onMouseClick();
public:
	BattleField(sf::RenderWindow *);
	void draw();
	void setPos(float, float);
	void setEdit(EditState);
	void setShipSize(ShipSize);
	
};