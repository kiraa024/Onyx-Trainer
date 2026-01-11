#pragma once
#include "../../../ext/ScriptHookV/script.h"
#include "../../../ext/ScriptHookV/natives.h"

namespace Features
{
    // add your bools/floats/states here etc
    extern bool g_GodMode;
    extern bool g_InvisiblePlayer;

    void PlayerUpdate(); // This runs every frame, even if menu is closed
}