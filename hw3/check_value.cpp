#include "functions.h" 

int check_value(int target_value, int &attempts_count){

	int current_value = 0;
	bool not_win = true;

	std::cout << "Enter your guess:" << std::endl;

	do {
		std::cin >> current_value;

		if (current_value < target_value) {
			std::cout << "less than " << current_value << std::endl;
			attempts_count ++;
		}
		else if (current_value > target_value) {
			std::cout << "greater than " << current_value << std::endl;
			attempts_count ++;
		}
		else {
			std::cout << "you win!" << std::endl;
			break;
		}

	} while(true);

	return 0;
}