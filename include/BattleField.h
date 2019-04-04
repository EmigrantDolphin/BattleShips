#include <SFML/Graphics.hpp>
#include <RectShapeEnh.h>
class BattleField{
public:
	enum EditState {Horizontal, Vertical, None};
	enum ShipSize {Two, Three, Four, Five};
private:
	sf::RenderWindow *window;
	EditState editState = EditState::Horizontal;
	ShipSize shipSize = ShipSize::Five;

	int fiveShipsFree = 1, fourShipsFree = 2, threeShipsFree = 3, twoShipsFree = 4;
	int fiveShipsPlaced = 0, fourShipsPlaced = 0, threeShipsPlaced = 0, twoShipsPlaced = 0;
	
	float posX = 10, posY = 10;
	static const int FieldWidth = 10, FieldHeight = 10, RectSize = 30, RectThickness = 1;
	RectShapeEnh fieldArr[FieldWidth][FieldHeight];
	sf::RectangleShape fieldBounds; // to make edges same as inner lines

	sf::Vector2i selectedRectPos;
	
	void createField();
	int getShipSize();
	void onMouseHover();
	void hoverShipH(); //used in onMouseHover to draw hovering ship, not yet placed
	void hoverShipV();
	bool doesHorizFit();
	bool doesVertiFit();
	bool isNoOneAroundH();
	bool isNoOneAroundV();
	void onMouseClick();
	void selectRect();
public:
	BattleField(sf::RenderWindow *);
	void draw();
	void setPos(float, float);
	void setEdit(EditState);
	void setShipSize(ShipSize);
	
};