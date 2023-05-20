#ifndef LOST_IN_SPACE
#define LOST_IN_SPACE

#include "splashkit.h"
#include "player.h"
#include "powerup.h"
#include "enemy.h"
#include "score.h"
#include <vector>

using std::vector;

// Structure to hold game data
struct game_data
{
    player_data player;             // Player data
    enemy_data  enemy;              // Enemy data
    vector<powerup_data> powerups;  // Vector to store powerup data
    score_data  score;              // Score data
};

// Load game resources
void load_resources();

// Draw the heads-up display (HUD)
void draw_hud(game_data &game);

// Add a powerup to the game
void add_powerup(game_data &game);

// Remove a powerup from the game
void remove_powerup(game_data &game, int index);

// Apply a powerup to the player
void apply_powerup(game_data &game, int i);

// Check for collisions between player and powerups
void check_collisions(game_data &game);

// Create a new game instance
game_data new_game();

// Draw the game on the screen
void draw_game(game_data &game);

// Update the game state
void update_game(game_data &game);

void restart_game(game_data& game);

bool should_end_game(const game_data& game);

#endif
