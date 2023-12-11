// status.cpp, contains code for entity status effects and curses/blessings
#include "status.hpp"

// class Status

void Status::set_defaults() {
	set_effect(EFFECT_TYPE::DAMAGE_OFFSET, 0);
	set_effect(EFFECT_TYPE::DAMAGE_MULTIPLIER, 1);
	set_effect(EFFECT_TYPE::DAMAGE_LIMITER, -1);
	set_effect(EFFECT_TYPE::HEALTH_OFFSET, 0);
	set_effect(EFFECT_TYPE::HEALTH_LIMITER, -1);
	set_effect(EFFECT_TYPE::HEALTH_REGENERATION, 0);
}

void Status::set_effect(EFFECT_TYPE effect, double strength) {
	effects[effect] = strength;
}

Status::Status(STATUS_TYPE type) {
	set_defaults();
	switch (type) {
	case STATUS_TYPE::CURSE_ONE_HEALTH:
		effects[EFFECT_TYPE::HEALTH_LIMITER] = 1;
		break;
	case STATUS_TYPE::TEMPORARY_REGENERATION_WEAK:
		effects[EFFECT_TYPE::HEALTH_REGENERATION] = 0.005;
		break;
	case STATUS_TYPE::TEMPORARY_STRENGTH_WEAK:
		effects[EFFECT_TYPE::DAMAGE_OFFSET] = 2;
		break;
	}
}

double Status::get_effect(EFFECT_TYPE effect) {
	return effects[effect];
}

// class Temporary_Status

Temporary_Status::Temporary_Status(STATUS_TYPE type, int actions) : Status(type), actions_left(actions) {}

int Temporary_Status::get_actions() {
	return actions_left;
}

void Temporary_Status::set_actions(int actions) {
	actions_left = actions;
}

// class Entity_Status

void Entity_Status::update(int actions) {
	for (size_t i = 0; i < temporary_status.size(); ++i) {
		Temporary_Status& t = temporary_status[i];
		t.set_actions(t.get_actions() - actions);
		if (t.get_actions() <= 0) {
			temporary_status.erase(temporary_status.begin() + i);
		}
	}
}

void Entity_Status::add_permanent_status(Status status) {
	permanent_status.push_back(status);
}

void Entity_Status::add_temporary_status(Temporary_Status status) {
	temporary_status.push_back(status);
}

double Entity_Status::get_effect(EFFECT_TYPE effect) {
	double total;

	// REMEMBER: every EFFECT_TYPE MUST have a case in this switch statement
	// There are three overall types of effect:
	switch (effect) {
	case EFFECT_TYPE::DAMAGE_OFFSET:
	case EFFECT_TYPE::HEALTH_OFFSET:
	case EFFECT_TYPE::HEALTH_REGENERATION:
		// additive
		total = 0;
		for (Temporary_Status s : temporary_status) {
			total += s.get_effect(effect);
		}
		for (Status s : permanent_status) {
			total += s.get_effect(effect);
		}
		break;
	case EFFECT_TYPE::DAMAGE_MULTIPLIER:
		// multiplicative
		total = 1;
		for (Temporary_Status s : temporary_status) {
			total *= s.get_effect(effect);
		}
		for (Status s : permanent_status) {
			total *= s.get_effect(effect);
		}
		break;
	case EFFECT_TYPE::DAMAGE_LIMITER:
	case EFFECT_TYPE::HEALTH_LIMITER:
		// and limiting
		total = -1;
		double limit;
		for (Temporary_Status s : temporary_status) {
			if ((limit = s.get_effect(effect)) < total || total == -1) {
				total = limit;
			}
		}
		for (Status s : permanent_status) {
			if ((limit = s.get_effect(effect)) < total || total == -1) {
				total = limit;
			}
		}
		break;
	}

	// if the above switch statement is written correctly there are no paths where total is uninitialized
	return total;
}
