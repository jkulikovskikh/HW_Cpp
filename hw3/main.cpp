#include "functions.h"

int main(int argc, char** argv) {

	int max_number = max_value; 

	if (argc >= 2) {

		std::string arg1_value{ argv[1] };
		if (arg1_value == "-max") {
			max_number = std::stoi(argv[2]);
		}
		else if (arg1_value == "-table")
		{
			read_high_score_file(high_scores_filename);
			return 0;
		}
		else if (arg1_value == "-level")
		{
			int level =  std::stoi(argv[2]);
			switch (level)
			{
			case 1:
				max_number = max_value_1;
				break;
			case 2:
				max_number = max_value_2;
				break;
			case 3:
				max_number = max_value_3;
				break;
			default:
				break;
			}
		}
	}

	// Ask about name
	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;

	int attempts_count = 1;
	check_value(generate_random_value(max_number), attempts_count);

	// Get the last high score
	if (std::cin.fail()) {
		std::cout << "Bad value!" << std::endl;
		return -1;
	}

	// Write new high score to the records table
	write_high_score_file(high_scores_filename, user_name, attempts_count);

	// Read the high score file and print all results
	read_high_score_file(high_scores_filename);

	return 0;
}
