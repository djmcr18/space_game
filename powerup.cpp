#include "powerup.h"
#include "splashkit.h"

const int MIN = -1500;
const int MAX = 1500;

// Returns a bitmap for a given powerup kind
bitmap powerup_bitmap(powerup_kind kind)
{
    // Select the bitmap based on the powerup kind
    switch (kind)
    {
        case FUEL:
            return bitmap_named("fuel");
        case HEART:
            return bitmap_named("heart");
        case CASH:
            return bitmap_named("cash");
        case BATTERY:
            return bitmap_named("battery");
        case DIAMOND:
            return bitmap_named("diamond");
        case BULLET:
            return bitmap_named("bullet");
        default:
            return bitmap_named("fuel"); // Default to fuel if the kind is invalid
    }
}

// Creates a new powerup with a random kind at the specified position
void new_powerup(vector<powerup_data> &powerups, double x, double y)
{
    powerup_data new_powerup_data;

    // Generate a random powerup kind
    new_powerup_data.kind = static_cast<powerup_kind>(rnd(6));

    // Create a sprite with the corresponding bitmap for the selected kind
    new_powerup_data.powerup_sprite = create_sprite(powerup_bitmap(new_powerup_data.kind));

    // Set the sprite's position
    sprite_set_x(new_powerup_data.powerup_sprite, x);
    sprite_set_y(new_powerup_data.powerup_sprite, y);

    // Set the sprite's x and y velocity to a random value between -2 and 2
    sprite_set_dx(new_powerup_data.powerup_sprite, rnd() * 4 - 2);
    sprite_set_dy(new_powerup_data.powerup_sprite, rnd() * 4 - 2);

    // Add the new powerup data to the vector
    powerups.push_back(new_powerup_data);
}

// Draws all powerup sprites in the powerups vector
void draw_powerup(vector<powerup_data> &powerups)
{
    for (const auto &powerup : powerups) 
    {
        draw_sprite(powerup.powerup_sprite);
    }
}

// Updates all powerup sprites in the powerups vector
void update_powerup(vector<powerup_data> &powerups)
{
    for (auto &powerup : powerups) 
    {
        update_sprite(powerup.powerup_sprite);
    }

    // Iterate over all the power-ups
    for (int i = 0; i < powerups.size(); i++)
    {
        // Get the current power-up sprite's position
        point_2d powerupPos = sprite_position(powerups[i].powerup_sprite);

        // Check if the power-up sprite is within the boundary
        if (powerupPos.x < MIN || powerupPos.x > MAX || powerupPos.y < MIN || powerupPos.y > MAX)
        {
            // Remove the powerup from the vector
            free_sprite(powerups[i].powerup_sprite);
            powerups.erase(powerups.begin() + i);
            i--; // Decrement the index as the powerup was removed
        }
    }
}