// ai.cpp
#include "ai.hpp"

#include <cmath>

#include "entity.hpp"
#include "player.hpp"
#include "random.hpp"
#include "world.hpp"

void AI::move_random(Level& level, Living_Entity* ent) {
	int amount = irandom(-1, 1);
	if (brandom()) {
		ent->move(level, ent->x + amount, ent->y);
	}
	else {
		ent->move(level, ent->x, ent->y + amount);
	}
}

void AI::move_towards_player(Level& level, Living_Entity* ent) {
	if (ent->seen_player) {
		int xoffs = ent->last_player_x < ent->get_x() ? -1 : 1;
		int yoffs = ent->last_player_y < ent->get_y() ? -1 : 1;
		if (std::abs(ent->last_player_x - ent->get_x()) > std::abs(ent->last_player_y - ent->get_y()) && level.can_walk(ent->get_x() + xoffs, ent->get_y())) {
			// The x distance is larger than the y distance and the tile in the x direction is available
			ent->move(level, ent->get_x() + xoffs, ent->get_y());
		}
		else if (level.can_walk(ent->get_x(), ent->get_y() + yoffs)) {
			// the tile in the y direction is available
			ent->move(level, ent->get_x(), ent->get_y() + yoffs);
		}
		else {
			// can't find a way to the player
			ent->seen_player = false;
		}

		if (ent->get_x() == ent->last_player_x && ent->get_y() == ent->last_player_y) {
			ent->seen_player = false;
		}
	}
}

void AI::attack_or_wander(Level& level, Living_Entity* ent) {
	if (ent->seen_player) {
		move_towards_player(level, ent);
	}
	else {
		move_random(level, ent);
	}
}
