#include "score.h"
#include "splashkit.h"

string to_string_with_precision(const double value, const int precision)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    return out.str();
}

string read_string(const string& prompt)
{
    write(prompt);
    return read_line();
}

score_data new_score_data()
{
    score_data score;

    score.cash_score = 0;
    score.diamond_score = 0;
    score.battery_score = 0;
    score.elapsed_time = 0;

    return score;
}

void update_elapsed_time(score_data& score)
{
    score.elapsed_time = current_ticks() / 1000; // Elapsed time in seconds
}

void save_score(const score_data& score)
{
    std::ofstream file("scores.txt", std::ios::app);
    if (file)
    {
        file << score.cash_score << "," << score.diamond_score << ","
             << score.battery_score << "," << score.elapsed_time << "\n";
        file.close();
    }
    else
    {
        write_line("Error: Failed to open scores.txt for writing!");
    }
}

score_data load_high_score()
{
    score_data high_score;
    high_score.cash_score = INT_MIN;        // Initialize cash_score with minimum value
    high_score.diamond_score = INT_MIN;     // Initialize diamond_score with minimum value
    high_score.battery_score = INT_MIN;     // Initialize battery_score with minimum value
    high_score.elapsed_time = __DBL_MIN__;     // Initialize elapsed_time with minimum value

    std::ifstream file("scores.txt");
    if (file)
    {
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);

            int cash_score;
            int diamond_score;
            int battery_score;
            double elapsed_time;

            ss >> cash_score;
            ss.ignore();
            ss >> diamond_score;
            ss.ignore();
            ss >> battery_score;
            ss.ignore();
            ss >> elapsed_time;

            if (cash_score > high_score.cash_score)
            {
                high_score.cash_score = cash_score;
            }
            if (diamond_score > high_score.diamond_score)
            {
                high_score.diamond_score = diamond_score;
            }
            if (battery_score > high_score.battery_score)
            {
                high_score.battery_score = battery_score;
            }
            if (elapsed_time > high_score.elapsed_time)
            {
                high_score.elapsed_time = elapsed_time;
            }
        }
        file.close();
    }
    else
    {
        write_line("Error: Failed to open scores.txt for reading!");
    }

    return high_score;
}

void restart_program()
{
    close_current_window();
    system("./lost_in_space3"); // Replace with the actual name of your program executable
    exit(0);
}

// Display the end screen for a specific duration and then close the program
void display_end_screen(score_data& score)
{
    clear_screen(COLOR_BLACK);

    save_score(score);

    // Load the high score
    score_data high_score = load_high_score();

    while (!quit_requested())
    {
        process_events();

        clear_screen(COLOR_BLACK);

        // Display end screen
        draw_text("GAME OVER", COLOR_RED, "space_font", 80, screen_width() / 2 - 40, screen_height() / 2 - 300, option_to_screen());

        draw_text("YOUR SCORES", COLOR_YELLOW, "space_font", 60, screen_width() / 2 - 205, screen_height() / 2 - 200, option_to_screen());
        draw_text("Cash Score: " + to_string(score.cash_score), COLOR_LIGHT_YELLOW, "space_font", 40, screen_width() / 2 - 215, screen_height() / 2 - 100, option_to_screen());
        draw_text("Diamond Score: " + to_string(score.diamond_score), COLOR_LIGHT_YELLOW, "space_font", 40, screen_width() / 2 - 220, screen_height() / 2, option_to_screen());
        draw_text("Battery Score: " + to_string(score.battery_score), COLOR_LIGHT_YELLOW, "space_font", 40, screen_width() / 2 - 220, screen_height() / 2 + 100, option_to_screen());
        draw_text("Time Survived: " + to_string_with_precision(score.elapsed_time, 2) + " seconds", COLOR_LIGHT_YELLOW, "space_font", 40, screen_width() / 2 - 270, screen_height() / 2 + 200, option_to_screen());

        draw_text("HIGH SCORES", COLOR_BRIGHT_GREEN, "space_font", 60, screen_width() / 2 + 110, screen_height() / 2 - 200, option_to_screen());
        draw_text("Highest Cash Score: " + to_string(high_score.cash_score), COLOR_LIGHT_GREEN, "space_font", 40, screen_width() / 2 + 75, screen_height() / 2 - 100, option_to_screen());
        draw_text("Highest Diamond Score: " + to_string(high_score.diamond_score), COLOR_LIGHT_GREEN, "space_font", 40, screen_width() / 2 + 70, screen_height() / 2, option_to_screen());
        draw_text("Highest Battery Score: " + to_string(high_score.battery_score), COLOR_LIGHT_GREEN, "space_font", 40, screen_width() / 2 + 70, screen_height() / 2 + 100, option_to_screen());
        draw_text("Longest Time Survived: " + to_string_with_precision(high_score.elapsed_time, 2) + " seconds", COLOR_LIGHT_GREEN, "space_font", 40, screen_width() / 2 + 23, screen_height() / 2 + 200, option_to_screen());

        draw_text("Press 'esc' to Exit", COLOR_WHITE, "space_font", 60, screen_width() / 2 - 75, screen_height() / 2 + 320, option_to_screen());
        draw_text("Press 'r' to Restart", COLOR_WHITE, "space_font", 60, screen_width() / 2 - 75, screen_height() / 2 + 350, option_to_screen());

        refresh_screen();

        while (true)
        {
            if (key_typed(R_KEY))
            {
                restart_program();
                return;
            }
            else if (key_typed(ESCAPE_KEY))
            {
                close_current_window();
                exit(0);
            }

            process_events();
        }
    }
}