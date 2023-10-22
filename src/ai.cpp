// ai.cpp
#include "ai.hpp"

#include "entity.hpp"
#include "world.hpp"

void AI::move_random(Level& level, Living_Entity* ent) {
	ent->move(level, ent->x + 1, ent->y);
}
