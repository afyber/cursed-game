// message.cpp
#include "message.hpp"

#include "libtcod.hpp"

#include "draw.hpp"

const int MESSAGE_BUFFER_SIZE = 25;

int messagec = 0;
Message messages[MESSAGE_BUFFER_SIZE];

void shift_messages() {
	for (int i = MESSAGE_BUFFER_SIZE - 2; i >= 0; --i) {
		messages[i + 1] = messages[i];
	}

	if (messagec != MESSAGE_BUFFER_SIZE - 1) {
		++messagec;
	}
}

void send_message(const char* str, Color color) {
	shift_messages();
	messages[0] = { str, color };
}

void draw_messages(tcod::Console& con, int x, int y, int width, int height) {
	int current_y = y + height;
	for (int i = 0; i < messagec; ++i) {
		int message_height = tcod::get_height_rect(width, messages[i].str);
		tcod::print_rect(con, { x, current_y - message_height, width, message_height }, messages[i].str, color_to_tcod(messages[i].color), std::nullopt);
		
		current_y -= message_height + 1;
		if (current_y < 0) {
			break;
		}
	}
}
