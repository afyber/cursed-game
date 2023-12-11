// status.hpp
#ifndef CURSED_STATUS_HPP_
#define CURSED_STATUS_HPP_
#include <unordered_map>
#include <vector>

using std::size_t;

// REMEMBER: if you add an effect it also needs to be added to the switch statement in Entity_Status::get_effect(EFFECT_TYPE)
enum class EFFECT_TYPE {
	DAMAGE_OFFSET,
	DAMAGE_LIMITER,
	DAMAGE_MULTIPLIER,
	HEALTH_OFFSET,
	HEALTH_LIMITER,
	HEALTH_REGENERATION
};

enum class STATUS_TYPE {
	CURSE_ONE_HEALTH,
	TEMPORARY_REGENERATION_WEAK,
	TEMPORARY_STRENGTH_WEAK
};

class Status {
private:
	std::unordered_map<EFFECT_TYPE, double> effects;

	void set_defaults();

protected:
	void set_effect(EFFECT_TYPE effect, double strength);

public:
	Status(STATUS_TYPE type);

	double get_effect(EFFECT_TYPE effect);
};

class Temporary_Status : public Status {
private:
	int actions_left;

public:
	Temporary_Status(STATUS_TYPE type, int actions);

	int get_actions();

	void set_actions(int actions);
};

class Entity_Status {
private:
	std::vector<Status> permanent_status;
	std::vector<Temporary_Status> temporary_status;

public:
	void update(int actions);

	void add_permanent_status(Status status);

	void add_temporary_status(Temporary_Status status);

	double get_effect(EFFECT_TYPE effect);
};

#endif
