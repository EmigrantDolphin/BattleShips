#include <SFML/Graphics.hpp>

class BattleField{
private:
	sf::RenderWindow *window;
	
	int posX = 10, posY = 10;
	static const int FieldWidth = 10, FieldHeight = 10, RectSize = 30, RectThickness = 3;
	sf::RectangleShape fieldArr[FieldWidth][FieldHeight];
	
	void createField();
public:
	BattleField(sf::RenderWindow *);
	void draw();
	
};