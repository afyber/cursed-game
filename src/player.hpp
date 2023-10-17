// player.hpp
#ifndef CURSED_PLAYER_HPP_
#define CURSED_PLAYER_HPP_
#include "world.hpp"

class Player : public Entity {
private:
	int health;

	void move(Level* level, int x, int y);

public:
	Player(int x, int y);

	void update(Level* level);

	bool is_solid();

	void hurt(Cursed_Attack attack);

	bool is_alive();
};

#endif