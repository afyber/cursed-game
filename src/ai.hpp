// ai.hpp
#ifndef CURSED_AI_HPP_
#define CURSED_AI_HPP_
#include "definitions.hpp"

class AI {
public:
	static void move_random(Level& level, Living_Entity* ent);

	static void move_towards_player(Level& level, Living_Entity* ent);
};

#endif
