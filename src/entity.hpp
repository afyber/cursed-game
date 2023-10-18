// entity.hpp
#ifndef CURSED_ENTITY_HPP_
#define CURSED_ENTITY_HPP_
#include "world.hpp"

struct Resistances {
	double normal_resistance;
	double magic_resistance;
	double fire_resistance;
};

class Living_Entity : public Entity {
protected:
	int health;
	int max_health;
	Resistances resistances;

	void move(Level* level, int x, int y);

public:
	Living_Entity(int x, int y, int max_health);

	void update(Level* level);

	bool is_solid();

	void hurt(Attack attack);

	bool is_alive();
};

#endif
