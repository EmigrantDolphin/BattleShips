#ifndef _BUTTONH_
#define _BUTTONH_

#include <SFML/Graphics.hpp>
#include "GameMaster.h"
#include "IDrawable.h"
#include "IClickable.h"
#include <functional>
#include <iostream>

class Button : public IDrawable, public IClickable{
private:
	std::function<void (void)> func;
	sf::Text text;
	sf::RectangleShape border;
	sf::Font font;
	float textSize;
	float borderThickness;
	
	
public:
	Button(std::function<void (void)>);
	void draw(sf::RenderWindow &);
	void onMouseClick();
	
	void setPosition(float, float);
	void setText(std::string);
	void setWidth(float);
	
	void select();
	void deselect();
	
	float getWidth();
};

#endif