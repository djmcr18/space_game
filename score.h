#ifndef SCORE_H
#define SCORE_H

#include <string>
#include "splashkit.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

struct score_data
{
    int cash_score;
    int diamond_score;
    int battery_score;
    double elapsed_time;
};

string to_string_with_precision(const double value, const int precision);

// Initialize the score module
score_data new_score_data();

// Update the elapsed time based on the delta time
void update_elapsed_time(score_data& score);

// Update the powerup score with the value obtained from a powerup
void update_powerup_score(score_data& score, int powerup_value);

void save_score(const score_data& score);

score_data load_high_score();

// Display the end screen with the player's score and elapsed time
void display_end_screen(score_data& score);

#endif /* SCORE_H */