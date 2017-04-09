#include <stdio.h>
#include <SDL.h>
#include "Joystick.h"

JoypadController *JoypadController::m_controllers[MAX_CONTROLLERS] = {0};

int main(int argc, char* args[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    JoypadController jc;

    printf("JoypadController: 0x%0x\n", &jc);

    // Start up SDL and create window
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_GAMECONTROLLER) != 0) {
        SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    } else {
        // Main loop flag
        bool quit = false;

        // Joystick
        SDL_JoystickEventState(SDL_ENABLE);

        if (SDL_CreateWindowAndRenderer(320, 240, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
            return 3;
        }

        // Event handler
        SDL_Event e;

        // Clear screen
        SDL_RenderClear(renderer);

        // Update screen
        SDL_RenderPresent(renderer);

        // Print number of joysticks found
        printf("%d joysticks detected!\n", SDL_NumJoysticks());
        
        // Forcefully update joysticks
        SDL_JoystickUpdate();

        // While application is running
        while(!quit) {
            // Handle events on queue
            while(SDL_PollEvent( &e ) != 0) {
                // User requests quit
                if(e.type == SDL_QUIT) {
                    quit = true;
                } else {
                    jc.processEvent(&e);
                }
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
