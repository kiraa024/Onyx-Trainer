# Onyx Trainer Base

Onyx Trainer Base is an **expanded GTA5-ASI-MenuBase** project featuring an **ImGui overlay** for in-game enhancements and a modular system for adding new features.

> ⚠️ **Disclaimer:** Use responsibly. Trainer tools modify game behavior. Only use in single-player/private environments to avoid violating game terms of service.

---

## Features

- Overlay Menu with ImGui  
- God Mode for the player  
- Invisible Player (Local)  
- Toggleable Watermark  
- Safe DLL unloading  
- Modular system for adding new features via `features/` folder

---

## Project Structure
/features/ -> Custom feature modules (player, vehicles, etc.)
/ext/ -> External dependencies
/ext/ImGui/ -> GUI library used for overlay
/ext/MinHook/ -> Hooking library for DirectX and functions
/ext/ScriptHookV/ -> GTA5 ScriptHook SDK
/theme/ -> Menu themes (colors, styles)
/src/ -> Core overlay implementation

---

## Installation

1. Download Source Code
2. Run the .sln file
3. Build in Debug x64 (didnt test Release but should work)
4. Enjoy!
