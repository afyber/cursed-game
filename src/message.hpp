// message.hpp
#ifndef CURSED_MESSAGE_HPP_
#define CURSED_MESSAGE_HPP_
#include "draw.hpp"

struct Message {
	const char* str;
	Color color;
	int frames_left;
};

void send_message(const char* str, Color color);

void update_messages();

void draw_messages(tcod::Console& con, int width, int height);

#endif
