#ifndef LOST_IN_SPACE_POWER_UP
#define LOST_IN_SPACE_POWER_UP

#include "splashkit.h"
#include <vector>

using namespace std;

/**
 * Different types of power-ups that can be collected by the player.
 */
enum powerup_kind
{
    FUEL,       // Adds fuel to the player's ship
    HEART,      // Adds health to the player
    CASH,       // Adds cash score to the player
    BATTERY,    // Adds battery to the player's ship
    DIAMOND,    // Adds diamond to the player's diamond count
    BULLET      // Adds bullets to the player's bullet count and removes health
};

/**
 * Struct containing the data for a power-up.
 * 
 * @field   powerup_sprite  The power-up's sprite - used to track position and movement
 * @field   kind            The type of power-up
 */
struct powerup_data
{
    sprite         powerup_sprite;
    powerup_kind   kind;
};

/**
 * Returns the bitmap associated with the given power-up type.
 * 
 * @param kind  The type of power-up to get the bitmap for
 * @returns     The bitmap associated with the given power-up type
 */
bitmap powerup_bitmap(powerup_kind kind);

/**
 * Creates a new power-up at the given position with a random type.
 * 
 * @param x     The x coordinate for the new power-up
 * @param y     The y coordinate for the new power-up
 * @returns     The new power-up data
 */
void new_powerup(vector<powerup_data> &powerups, double x, double y);

/**
 * Draws the given power-up to the screen.
 * 
 * @param powerups  The power-up to draw to the screen
 */
void draw_powerup(vector<powerup_data> &powerups);

/**
 * Actions a step update of the given power-up - moving it and checking for collision with the player.
 * 
 * @param powerups   The power-up being updated
 */
void update_powerup(vector<powerup_data> &powerups);

#endif