#include <SFML/Graphics.hpp>

class BattleField{
private:
	sf::RenderWindow *window;
	
	float posX = 10, posY = 10;
	static const int FieldWidth = 10, FieldHeight = 10, RectSize = 30, RectThickness = 1;
	sf::RectangleShape fieldArr[FieldWidth][FieldHeight];
	sf::RectangleShape fieldBounds; // to make edges same as inner lines
	
	void createField();
	void onMouseHover();
public:
	BattleField(sf::RenderWindow *);
	void draw();
	void setPos(float, float);
	
};