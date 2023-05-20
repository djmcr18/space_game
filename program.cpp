// Yotube link for screen recording of program running:
// https://youtu.be/wRZnKWeeUkA
// Thanks! :)

#include "splashkit.h"
#include "lost_in_space.h"

game_data game;

int main()
{
    // Open the window and load in the game resources.
    open_window("Lost In Space", 800, 800);
    load_resources();

    // Create the player and powerup objects
    game.player = new_player();

    while (!should_end_game(game))
    {
        // Handle input to adjust player movement
        process_events();
        
        handle_input(game.player);

        // Perform movement and update the camera
        update_game(game);

        clear_screen(COLOR_BLACK);

        // Clear the screen and redraw the HUD, player and powerups
        draw_game(game);
    }

    display_end_screen(game.score);

    return 0;
}