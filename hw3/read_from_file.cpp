#include "functions.h"

int read_high_score_file(std::string filename){

    std::ifstream in_file{high_scores_filename};
	if (!in_file.is_open()) {
		std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
		return -1;
	}

	std::cout << "High scores table:" << std::endl;

	std::string username;
	int high_score = 0;

	std::map<std::string, unsigned int> scores;
	while (true) {
		// Read the username first
		in_file >> username;
		// Read the high score next
		in_file >> high_score;
		// Ignore the end of line symbol
		in_file.ignore();

		if (in_file.fail()) {
			break;
		}

		if (scores.count(username)){
			if (scores[username] > high_score){
				scores[username] = high_score;
			}
		}
		else {
			scores[username] = high_score;
		}
	}

	// Print the minimum number of attempts to the screen 
	std::map<std::string, unsigned> :: iterator it = scores.begin();
	for (it; it != scores.end(); it++) {
		std::cout << it -> first << '\t' << it -> second << std::endl;
	}

	return 0;
}