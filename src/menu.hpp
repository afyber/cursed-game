// menu.hpp
#ifndef CURSED_MENU_HPP_
#define CURSED_MENU_HPP_
#include "libtcod.hpp"

union Menu_Value {
	bool b;
	int i;
	double d;
	const char* str;
};

enum class Menu_Type {
	CHOICE
};

class Menu {
public:
	virtual ~Menu();

	virtual void update() = 0;

	virtual void draw(tcod::Console& con) = 0;

	virtual Menu_Type get_type() = 0;
};

void menu_return(Menu_Value v);

bool menu_returned();

Menu_Value menu_recieve();

void menu_push(Menu* m);

bool menu_open();

void update_menus();

void draw_menus(tcod::Console& con);

class Choice_Menu : public Menu {
private:
	const char* message;
	const int lines;
	bool selected;

public:
	Choice_Menu(const char* message);

	void update();

	void draw(tcod::Console& con);

	Menu_Type get_type();
};

#endif
