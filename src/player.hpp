// player.hpp
#ifndef CURSED_PLAYER_HPP_
#define CURSED_PLAYER_HPP_
#include "entity.hpp"
#include "world.hpp"

class Player : public Living_Entity {
public:
	Player(int x, int y);

	bool update(Level& level);

	void draw(tcod::Console& con);
};

#endif
