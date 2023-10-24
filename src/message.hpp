// message.hpp
#ifndef CURSED_MESSAGE_HPP_
#define CURSED_MESSAGE_HPP_
#include "draw.hpp"

struct Message {
	const char* str;
	Color color;
};

void send_message(const char* str, Color color);

void draw_messages(tcod::Console& con, int x, int y, int width, int height);

#endif
