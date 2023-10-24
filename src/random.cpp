// random.cpp, has several random number utilities
#include "random.hpp"

#include <random>

std::default_random_engine engine;

void setup_random() {
	std::random_device r;
	engine = std::default_random_engine(r());
}

bool brandom() {
	std::uniform_int_distribution<int> dist(0, 1);
	return dist(engine);
}

int irandom(int lower, int upper) {
	std::uniform_int_distribution<int> dist(lower, upper);
	return dist(engine);
}
