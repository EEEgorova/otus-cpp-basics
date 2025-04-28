#include "random_value.h"

#include <cstdlib>
#include <ctime>

int random_value() {

	const int max_value = 100;

	std::srand(std::time(nullptr)); // use current time as seed for random generator

	const int random_value = std::rand() % 100;

	return random_value;
}
