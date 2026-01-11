# Onyx Trainer Base (https://www.gta5-mods.com/scripts/onyx-trainer)

A GTA5 trainer overlay built with ImGui and ScriptHookV.  
This project serves as a base for custom feature modules, using DirectX hooks for rendering and input.

---

## Features

- God Mode (local player)
- Invisible Player (local)
- Toggleable overlay menu
- Watermark display
- DLL unload functionality
- Input blocking when menu is open

---

## Project Structure

- /features/ -> Custom feature modules (player, vehicles, etc.)  
- /ext/ -> External dependencies  
- /ext/ImGui/ -> GUI library used for overlay  
- /ext/MinHook/ -> Hooking library for DirectX and functions  
- /ext/ScriptHookV/ -> GTA5 ScriptHook SDK  
- /theme/ -> Menu themes (colors, styles)  
- /src/ -> Core overlay implementation  

---

## How to Use

1. Build the project as a DLL.
2. Inject into GTA5 using ScriptHookV.
3. Toggle the menu with `F4`.
4. Features like God Mode and Invisible Player work continuously, even when the menu is closed.
5. Unload the trainer safely via the "Unload DLL" button in the menu.

---

## Credits

- **ImGui** – [https://github.com/ocornut/imgui](https://github.com/ocornut/imgui)  
- **MinHook** – [https://github.com/TsudaKageyu/minhook](https://github.com/TsudaKageyu/minhook)  
- **ScriptHookV** – Alexander Blade (ScriptHookV SDK)  
- **Original Onyx Trainer Base Concept** – kiraa024  

---

## Showcase

<img width="1913" height="1077" alt="grafik" src="https://github.com/user-attachments/assets/4af8207e-81ac-484f-893f-451c7e9a96df" />

---

## License

This project is licensed under the **MIT License**. You are free to use, modify, and distribute the code as long as the original copyright and license notice are included.
