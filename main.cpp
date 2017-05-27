#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include "SDL/SDL_ttf.h"
#include "Player.h"

#define SPRITESIZE 20
#define WINDOWHEIGHT 480
#define WINDOWWIDTH 640
#define WINDOWCELLS WINDOWWIDTH/SPRITESIZE4

#define GAMEBACKGROUND "forestBackground.bmp"

void RefreshGameDisplay(SDL_Surface* screen, Player playerOne);

SDL_Surface* background = SDL_LoadBMP(GAMEBACKGROUND);

int main ( int argc, char** argv )
{

//    TTF_Init();

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(WINDOWWIDTH, WINDOWHEIGHT, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    Player playerOne = Player(screen);

    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    else
                        playerOne.Update(event.key.keysym.sym);


                }
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        _sleep(000);

        RefreshGameDisplay(screen, playerOne);

        playerOne.Draw(screen);

        // finally, update the screen :)
        SDL_Flip(screen);

    } // end main loop

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}

void RefreshGameDisplay(SDL_Surface* screen, Player playerOne)
{


    SDL_Rect rectangle;

    rectangle.x = 0;

    rectangle.y = 80;

    rectangle.w = screen->w;

    rectangle.h = screen->h;

    SDL_BlitSurface(background, 0, screen, &rectangle);

    //Floor

    rectangle.h = SPRITESIZE;

    rectangle.w = WINDOWWIDTH;

    rectangle.x = 0;

    rectangle.y = WINDOWHEIGHT - SPRITESIZE;

    SDL_FillRect(screen, &rectangle, SDL_MapRGB(screen->format, 0xaa, 0xaa, 0xaa));

    //Life bar

    rectangle.x = SPRITESIZE - 2;

    rectangle.y = SPRITESIZE - 2 + 10;

    rectangle.h = SPRITESIZE + 4;

    rectangle.w = 10 * SPRITESIZE + 4;
-
    SDL_FillRect(screen, &rectangle, SDL_MapRGB(screen->format, 0xff, 0xff, 0xff));

    rectangle.x = SPRITESIZE;

    rectangle.y = 10 + SPRITESIZE;

    rectangle.h = SPRITESIZE;

    double lifeSections = (10 * SPRITESIZE) / playerOne.GetMaxLife();

    double percentage = (playerOne.Getlife() * 100) / playerOne.GetMaxLife();

    rectangle.w = (10 * SPRITESIZE) * (percentage/100);

    SDL_FillRect(screen, &rectangle, SDL_MapRGB(screen->format, 0xff, 0x00, 0x00));

    rectangle.x = rectangle.x + rectangle.w + 24;

    rectangle.w = SPRITESIZE;

    rectangle.y = rectangle.y - 10;

    SDL_Surface* weaponLogo = SDL_LoadBMP("weaponLogoBlack.bmp");

    SDL_BlitSurface(weaponLogo, 0, screen, &rectangle);

    rectangle.x = rectangle.x + 10;

    // write atk

    rectangle.x += 40;

    SDL_Surface* armorLogo = SDL_LoadBMP("armorLogoBlack.bmp");

    SDL_BlitSurface(armorLogo, 0, screen, &rectangle);

}
