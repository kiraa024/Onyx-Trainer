#include "player.h"

namespace Features
{
    // add your bools/floats/states here etc
    bool g_GodMode = false;
    bool g_InvisiblePlayer = false;

    void PlayerUpdate()
    {
        // Get player Ped and ID
        Ped playerPed = PLAYER::PLAYER_PED_ID();
        Player playerId = PLAYER::PLAYER_ID();

        // Godmode
        ENTITY::SET_ENTITY_INVINCIBLE(playerPed, g_GodMode);
        PLAYER::SET_PLAYER_INVINCIBLE(playerId, g_GodMode);

        // Invisible
        ENTITY::SET_ENTITY_VISIBLE(playerPed, !g_InvisiblePlayer, false);
    }
}
