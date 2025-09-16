#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>


#include "./includes/chip8.h"
#include "./toot/tootlib.h"



int main(int argc, char const *argv[])
{
    struct chip8 chip8;
    SDL_Window * window;

    if (argc < 2)
    {
        printf("You must provide a file to load!\n");
        return -1;
    }

    const char * filename = argv[1];
    printf("Filename is: %s\n", filename);

    FILE * f = fopen(filename, "rb");
    if (!f)
    {
        printf("Error opening file %s \n", filename);
        return -1;
    }


    fseek(f, 0, SEEK_END); // move to the end of the file stream
    long size = ftell(f);  // get the size/position of the file
    fseek(f, 0, SEEK_SET); // move back to the beginning of the file


    // creates a buffer the size of the file
    char buf[size];
    // reads the full filestream into the buffer
    int res = fread(buf, size, 1, f);

    if (res != 1)
    {
        printf("failed to read from file \n");
        return -1;
    }


    chip8_init(&chip8);
    chip8_load(&chip8, buf, size);




    chip8_screen_draw_sprite(&chip8.screen, 62, 10, &chip8.memory.memory[0x14], 5);



    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        printf("SDL init error: %s", SDL_GetError());
    else 
    {
        window = SDL_CreateWindow( 
            EMU_WINDOW_TITLE, 
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, 
            CHIP8_WIDTH * SCREEN_MULTIPLIER, 
            CHIP8_HEIGHT * SCREEN_MULTIPLIER, 
            SDL_WINDOW_SHOWN 
        );


        SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);

        while(1) 
        {
            SDL_Event event;
            char key;
            int vkey = -1;

            while (SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_QUIT:
                        goto out;
                    break;

                    case SDL_KEYDOWN:
                        chip8_keyboard_down(&chip8.keyboard, event.key.keysym.sym);
                    break;

                    case SDL_KEYUP:
                        chip8_keyboard_up(&chip8.keyboard, event.key.keysym.sym);
                    break;
                }
             
            }


            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

            for (int x = 0; x < CHIP8_WIDTH; x++)
            {
                for (int y = 0; y < CHIP8_HEIGHT; y++)
                {
                    if (chip8_screen_is_set(&chip8.screen, x, y))
                    {
                        SDL_Rect r;
                        r.x = x * SCREEN_MULTIPLIER;
                        r.y = y * SCREEN_MULTIPLIER;
                        r.w = SCREEN_MULTIPLIER;
                        r.h = SCREEN_MULTIPLIER;
                        SDL_RenderFillRect(renderer, &r);
                    }
                }
            }
            SDL_RenderPresent(renderer);

            if (chip8.registers.delay_timer > 0)
            {
                SDL_Delay(100);
                chip8.registers.delay_timer -= 1;
                printf("Delay!!\n");
            }

            if (chip8.registers.sound_timer > 0)
            {
                // toot(60, 100 * chip8.registers.sound_timer);
                chip8.registers.sound_timer = 0;
            }  
        }
    }
    

out:
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
