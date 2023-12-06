// status.hpp
#ifndef CURSED_STATUS_HPP_
#define CURSED_STATUS_HPP_
#include <vector>

enum class EFFECT_TYPE {
	DAMAGE_OFFSET,
	DAMAGE_MULTIPLIER,
	DAMAGE_LIMITER,
	HEALTH_OFFSET,
	HEALTH_LIMITER,
	NUM_EFFECTS
};

struct Effect {
	EFFECT_TYPE type;
	double value;
};

class Status {
	std::vector<Effect> effects;
};

#endif
