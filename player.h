#ifndef LOST_IN_SPACE_PLAYER
#define LOST_IN_SPACE_PLAYER

#include "splashkit.h"

using namespace std;

#define PLAYER_SPEED 1.5
#define PLAYER_ROTATE_SPEED 3
#define SCREEN_BORDER 100

/**
 * Different options for the kind of ship.
 * Adjusts the image used.
 */
enum ship_kind
{
    AQUARII,
    GLIESE,
    PEGASI
};

/**
 * The player data keeps track of all of the information related to the player.
 * 
 * @field   player_sprite   The player's sprite - used to track position and movement
 * @field   kind            Current kind of player ship
 * @field   fuel_pct        The ship's fuel level
 * @field   bullet_count    The amount of bullets the player has in inventory
 * @field   health          The player's health level
 */
struct player_data
{
    sprite      player_sprite;
    ship_kind   kind;
    float       fuel_pct;
    int         bullet_count;
    float       health_pct;
};

/**
 * Creates a new player in the centre of the screen with the default ship.
 * 
 * @returns     The new player data
 */
player_data new_player();

/**
 * Draws the player to the screen. 
 * 
 * @param player    The player to draw to the screen
 */
void draw_player(const player_data &player);

/**
 * Actions a step update of the player - moving them and adjusting the camera.
 * 
 * @param player      The player being updated
 */
void update_player(player_data &player);

/**
 * Read user input and update the player based on this interaction.
 * 
 * @param player    The player to update
 */
void handle_input(player_data &player);

#endif 