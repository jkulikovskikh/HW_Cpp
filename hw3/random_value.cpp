#include "functions.h"

int generate_random_value(int max_value)
{
	std::srand(std::time(nullptr)); // use current time as seed for random generator

	int random_value = std::rand() % max_value;

	return random_value;
}
