// player.hpp
#ifndef CURSED_PLAYER_HPP_
#define CURSED_PLAYER_HPP_
#include "world.hpp"

class Player : public Entity {
private:
	void move(Level* level, int x, int y);

public:
	void update(Level* level);

	bool is_solid();

	void draw(tcod::Console& con);
};

#endif