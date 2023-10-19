// player.hpp
#ifndef CURSED_PLAYER_HPP_
#define CURSED_PLAYER_HPP_
#include "world.hpp"
#include "entity.hpp"

class Player : public Living_Entity {
public:
	Player(int x, int y);

	void update(Level* level);
};

#endif
