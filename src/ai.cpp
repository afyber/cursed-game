// ai.cpp
#include "ai.hpp"

#include "entity.hpp"
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
