#include <stdio.h>
#include <SDL2/SDL.h>

#include "./includes/chip8.h"

int main(int argc, char const *argv[])
{
    struct chip8 chip8;
    SDL_Window * window;

    chip8.registers.SP = 0;

    chip8_stack_push(&chip8, 0xff);
    chip8_stack_push(&chip8, 0x12);

    printf("%x \n", chip8_stack_pop(&chip8));
    printf("%x \n", chip8_stack_pop(&chip8));



    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        printf("SDL init error: %s", SDL_GetError());
    else 
    {
        window = SDL_CreateWindow( 
            EMU_WINDOW_TITLE, 
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, 
            CHIP8_WIDTH * CHIP8_WINDOW_MULTIPLIER, 
            CHIP8_HEIGHT * CHIP8_WINDOW_MULTIPLIER, 
            SDL_WINDOW_SHOWN 
        );


        SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);

        while(1) 
        {
            SDL_Event event;

            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                    goto out;
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_Rect r;
            r.x = 0;
            r.y = 0;
            r.w = 40;
            r.h = 40;
            SDL_RenderFillRect(renderer, &r);
            SDL_RenderPresent(renderer);
        }
        
        
        
    }
    

out:
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
