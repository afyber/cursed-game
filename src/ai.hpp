// ai.hpp
#ifndef CURSED_AI_HPP_
#define CURSED_AI_HPP_

class Level;
class Living_Entity;

class AI {
private:
	bool player_visible;
	int player_x, player_y;

public:
	void move_random(Level& level, Living_Entity* ent);
};

#endif
