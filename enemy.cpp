#include "enemy.h"
#include "splashkit.h"

bitmap  enemy_bitmap(enemy_kind kind)
{
    switch (kind)
    {
        case MARS:
            return bitmap_named("mars");
        case MERCURY:
            return bitmap_named("mercury");
        case JUPITER:
            return bitmap_named("jupiter");
        default:
            return bitmap_named("jupiter");
    }
}

// Create and initialize a new enemy
enemy_data new_enemy()
{
    enemy_data enemy;

    // Randomly choose an enemy kind
    enemy.kind = static_cast<enemy_kind>(rnd(static_cast<int>(MARS), static_cast<int>(JUPITER)));

    // Load the enemy bitmap based on the chosen kind
    enemy.enemy_sprite = create_sprite(enemy_bitmap(MARS));

    enemy.speed = 3;
    
    // Set the initial position of the enemy
    sprite_set_x(enemy.enemy_sprite, 800);
    sprite_set_y(enemy.enemy_sprite, 800);
    
    return enemy;
}

// Update the enemy's behavior to chase the player
void update_enemy(enemy_data &enemy, const player_data &player)
{
    // Get the position of the enemy and player
    point_2d enemy_pos = sprite_position(enemy.enemy_sprite);
    point_2d player_pos = sprite_position(player.player_sprite);

    // Calculate the direction from the enemy to the player
    float dx = player_pos.x - enemy_pos.x;
    float dy = player_pos.y - enemy_pos.y;
    float distance = sqrt(dx * dx + dy * dy);

    // Adjust the position of the enemy towards the player
    float speed = enemy.speed * distance / 100.0; // Adjust the divisor to control the chasing speed
    dx /= distance;
    dy /= distance;
    sprite_set_dx(enemy.enemy_sprite, dx * speed);
    sprite_set_dy(enemy.enemy_sprite, dy * speed);

    // Update the enemy sprite
    update_sprite(enemy.enemy_sprite);
}

// Draw the enemy on the screen
void draw_enemy(const enemy_data &enemy)
{
    draw_sprite(enemy.enemy_sprite);
}