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

		// calculate the manhattan distance to the player, this will be equal to 1 ONLY when we are on a tile adjacent to where we're trying to go
		int xdist = std::abs(ent->last_player_x - ent->get_x());
		int ydist = std::abs(ent->last_player_y - ent->get_y());
		if (xdist + ydist == 1) {
			// simply move the last step, needed so attacking the player doesn't cause the entity to think they can't find the player
			ent->move(level, ent->get_x() + xoffs, ent->get_y() + yoffs);
		}
		else if ((xdist > ydist || level.get_map().is_solid(ent->get_x(), ent->get_y() + yoffs))
			&& !level.get_map().is_solid(ent->get_x() + xoffs, ent->get_y())) {
			ent->move(level, ent->get_x() + xoffs, ent->get_y());
		}
		else if (!level.get_map().is_solid(ent->get_x(), ent->get_y() + yoffs)) {
			ent->move(level, ent->get_x(), ent->get_y() + yoffs);
		}
		else {
			// can't find a way to the player, so just go back to wandering
			ent->seen_player = false;
		}

		if (ent->get_x() == ent->last_player_x && ent->get_y() == ent->last_player_y) {
			// if we reached the point where we last saw the player, set to false so they start wandering again
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
