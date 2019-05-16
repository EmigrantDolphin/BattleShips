#ifndef _BUTTONH_
#define _BUTTONH_

#include <SFML/Graphics.hpp>
#include "IDrawable.h"
#include "IClickable.h"
#include <string>

class Button : public IDrawable, public IClickable{
private:
	void (* callback)();
	sf::Text text;
	sf::RectangleShape border;
	sf::Font font;
	float textSize;
	float borderThickness;
	
public:
	Button(void (*)());
	void draw();
	void onMouseClick();
	
	void setPosition(float, float);
	void setText(std::string);
};

#endif