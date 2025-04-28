#include "check_value.h"
#include "random_value.h"

#include <iostream>

int check_value() {

	const int target_value = random_value();
	int current_value = 0;
	int count = 0;

	std::cout << "Enter your guess:" << std::endl;

	while (true) {
		std::cin >> current_value;
		++count;
		if (current_value > target_value) {
			std::cout << "less than " << current_value << std::endl;
		}
		else if (current_value < target_value) {
			std::cout << "greater than " << current_value << std::endl;
		}
		else {
			std::cout << "you win! attempts = " << count << std::endl;
			break;
		}
	}

	return count;
}
