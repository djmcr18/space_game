#ifndef LOST_IN_SPACE_ENEMY
#define LOST_IN_SPACE_ENEMY

#include "splashkit.h"
#include "player.h"

using namespace std;

enum enemy_kind
{
    MARS,
    MERCURY,
    JUPITER
};

// Struct to hold the enemy data
struct enemy_data
{
    sprite enemy_sprite; // Sprite representing the enemy
    enemy_kind kind;
    float speed; // Speed at which the enemy moves
};

/**
 * Creates a new enemy with its initial position and speed.
 *
 * @return The newly created enemy
 */
enemy_data new_enemy();

/**
 * Updates the enemy's behavior, making it chase the player at a slower speed.
 *
 * @param enemy The enemy to update
 * @param player The player data for reference in chasing behavior
 */
void update_enemy(enemy_data &enemy, const player_data &player);

/**
 * Draws the enemy on the screen.
 *
 * @param enemy The enemy to draw
 */
void draw_enemy(const enemy_data &enemy);

#endif /* ENEMY_H */