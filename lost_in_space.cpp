#include "lost_in_space.h"
#include "splashkit.h"

// Declare global variable for game resoureces and data.
font space_font;
bitmap orange_bar;
bitmap green_bar_lines;
bitmap bar_grey_fill;
sound_effect powerup_sound;
sound_effect gunshot_sound;

/**
 * Load the game images, sounds, etc.
 */
void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");

    orange_bar = load_bitmap("orange_bar", "Resources/images/orange_bar.png");
    green_bar_lines = load_bitmap("green_bar_lines", "Resources/images/green_bar_lines.png");
    bar_grey_fill = load_bitmap("bar_grey_fill", "Resources/images/bar_grey_fill.png");
    space_font = load_font("PressStart2P", "PressStart2P.ttf");

    powerup_sound = load_sound_effect("powerup", "powerup.mp3");
    gunshot_sound = load_sound_effect("gunshot", "gunshot.mp3");
}

// Draw the HUD
void draw_hud(game_data &game)
{
    // Draw the purple ellipse background for the top left section of the HUD
    fill_ellipse(COLOR_WHITE, 22, 22, 356, 106, option_to_screen());
    fill_ellipse(COLOR_MEDIUM_PURPLE, 25, 25, 350, 100, option_to_screen());
    
    // Draw the labels/text in the HUD
    draw_text("LOCATION: " + point_to_string(center_point(game.player.player_sprite)), COLOR_WHITE, 50, 70, option_to_screen());
    draw_text("FUEL", COLOR_WHITE, 643, 70, option_to_screen());
    draw_text("SCORE: ", COLOR_WHITE, 105, 48, option_to_screen());
    draw_text(to_string(game.score.cash_score), COLOR_WHITE, 170, 48, option_to_screen());    
    draw_text("DMNDS: ", COLOR_WHITE, 105, 92, option_to_screen());
    draw_text(to_string(game.score.diamond_score), COLOR_WHITE, 170, 92, option_to_screen());
    draw_text(to_string(game.score.battery_score), COLOR_BRIGHT_GREEN, space_font, 30, 748, 740, option_to_screen());
    draw_text(to_string(game.player.bullet_count), COLOR_DARK_RED, space_font, 30, 40, 740, option_to_screen());

    // Draw the icons in the HUD
    draw_bitmap("battery", 640, 700, option_scale_bmp(0.7, 0.7, option_to_screen()));
    draw_bitmap("bullet", 75, 700, option_scale_bmp(0.7, 0.7, option_to_screen()));
    draw_bitmap("heart", 200, 710, option_scale_bmp(0.3, 0.3, option_to_screen()));
    draw_bitmap("bar_grey_fill", 500, 20, option_to_screen());
    float orange_bar_width = bitmap_width("orange_bar") * game.player.fuel_pct;
    draw_bitmap("orange_bar", 500, 20, option_part_bmp(0, 0, orange_bar_width, bitmap_height("orange_bar"), option_to_screen()));
    draw_bitmap("bar_grey_fill", 270, 737, option_to_screen());
    float green_bar_lines_width = bitmap_width("green_bar_lines") * game.player.health_pct;
    draw_bitmap("green_bar_lines", 270, 737, option_part_bmp(0, 0, green_bar_lines_width, bitmap_height("green_bar_lines"), option_to_screen()));
};

// Create a new game instance
game_data new_game()
{
    game_data game;
    game.player = new_player(); // Initialize the player
    game.enemy = new_enemy(); // Initialize the enemy
    game.score = new_score_data(); //Initialize score
    return game;
}

// Add a powerup to the game
void add_powerup(game_data &game)
{
    if (rnd() < 0.06) // Random chance of 3% to add a powerup
    {
        new_powerup(game.powerups, rnd(-1500, 1500), rnd(-1500, 1500)); // Create a new powerup at a random position
    }
}

// Remove a powerup from the game
void remove_powerup(game_data &game, int index)
{
    game.powerups.erase(game.powerups.begin() + index); // Remove the powerup at the specified index from the vector
}

void apply_powerup(game_data &game, int i)
{
    // Perform appropriate action based on powerup type
    switch (game.powerups[i].kind)
    {
        case FUEL:
            play_sound_effect(powerup_sound); // Play the powerup sound
            // Add 25% fuel to the player and remove fuel powerup
            game.player.fuel_pct += 0.25;
            if (game.player.fuel_pct > 1.0)
            {
                game.player.fuel_pct = 1.0;
            }
            remove_powerup(game, i);
            break;
        case HEART:
            play_sound_effect(powerup_sound); // Play the powerup sound
            // Add 0.14285714 to health_pct and remove heart powerup
            game.player.health_pct += 0.14285714;
            if (game.player.health_pct > 1.0)
            {
                game.player.health_pct = 1.0;
            }
            remove_powerup(game, i);
            break;
        case CASH:
            play_sound_effect(powerup_sound); // Play the powerup sound
            // TODO: Handle potion powerup
            game.score.cash_score += 100;                    
            remove_powerup(game, i); 
            break;
        case BATTERY:
            play_sound_effect(powerup_sound); // Play the powerup sound
            // Add 1 to battery counter and remove battery powerup
            game.score.battery_score += 1;
            remove_powerup(game, i);                    
            break;
        case DIAMOND:
            play_sound_effect(powerup_sound); // Play the powerup sound
            // Add 1 to diamond counter and remove diamond powerup
            game.score.diamond_score += 1;
            remove_powerup(game, i);                    
            break;
        case BULLET:
            play_sound_effect(gunshot_sound); // Play the gunshot sound
            // Remove 0.14285714 from health_pct, add 1 to bullet counter and remove bullet powerup
            game.player.health_pct -= 0.14285714 * 2;
            if (game.player.health_pct < 0.0)
            {
                game.player.health_pct = 0.0;
            }
            game.player.bullet_count += 1;
            remove_powerup(game, i);
            break;
    }
}

void check_collisions(game_data &game)
{
    // Loop backwards through all powerups in the game
    for (int i = game.powerups.size() - 1; i >= 0; i--)
    {
        // Check for collision with player sprite
        if (sprite_collision(game.player.player_sprite, game.powerups[i].powerup_sprite))
        {
            apply_powerup(game, i);
        }
    }
}

// Function to check if the game should end
bool should_end_game(const game_data& game)
{
    // If the player's health is zero, the game should end
    if (game.player.health_pct <= 0.0)
    {
        return true;
    }

    // If the player's fuel is zero, the game should end
    if (game.player.fuel_pct <= 0.0)
    {
        return true;
    }

    // Check if the window close event has been triggered
    if (quit_requested())
    {
        return true;
    }

    return false;
}

// Function to draw the game on the screen
void draw_game(game_data &game)
{
    draw_hud(game);           // Draw the HUD (Heads-Up Display)
    draw_player(game.player); // Draw the player
    draw_enemy(game.enemy);   // Draw the enemy
    draw_powerup(game.powerups); // Draw the powerups
    refresh_screen(60); // Refresh the screen at 60 frames per second
};

// Function to update the game state
void update_game(game_data &game)
{
    add_powerup(game);          // Add new powerups to the game
    check_collisions(game);     // Check for collisions between player and powerups
    update_player(game.player); // Update the player's position and animations
    update_enemy(game.enemy, game.player);   // Update the enemy's position and animations
    update_powerup(game.powerups); // Update the powerups' positions and animations
    update_elapsed_time(game.score);
};