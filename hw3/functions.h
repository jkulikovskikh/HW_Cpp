#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <map>

#pragma once

const int max_value = 100;
const int max_value_1 = 10;
const int max_value_2 = 50;
const int max_value_3 = 100;

const std::string high_scores_filename = "high_scores.txt";

// function generate random value
int generate_random_value(const int max_value);

// function check value and calc number of attempts
int check_value(int target_value, int &attempts_count);

// function write the high score in file
int write_high_score_file(std::string filename, std::string user_name, int attempts_count);

// function read the high score file and print all results
int read_high_score_file(std::string filename);