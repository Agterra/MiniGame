#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include "SDL/SDL_ttf.h"
#include "Player.h"
#include <iostream>
#include "Monster.h"

#define SPRITESIZE 20
#define WINDOWHEIGHT 480
#define WINDOWWIDTH 640
#define WINDOWCELLS WINDOWWIDTH/SPRITESIZE4

#define GAMEBACKGROUND "forestBackgroung.bmp"

using namespace std;

enum state
{

    GAMEOVER = 0,

    GAME,

    MENU,

};

void RefreshGameDisplay(SDL_Surface* screen, Player playerOne);

bool checkHitbox(Player aPlayer, Monster aMonster);

void applyDamages(const Player& aPlayer,const Monster& aMonster);

void DisplayGameOver(SDL_Surface* screen);

void DisplayMenu(SDL_Surface* screen);

state currentGameState = GAME;

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

    Monster monsterOne = Monster(screen, 5, 1, 0);//Life, attack, armor

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
                    {

                        if(currentGameState == MENU)
                            currentGameState = GAME;
                        else
                            currentGameState = MENU;

                    }
                    else
                    {

                        playerOne.Update(event.key.keysym.sym);

                        currentGameState = GAME;

                    }


                }
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        _sleep(500);



        switch(currentGameState)
        {
            case GAME:

                monsterOne.Update(playerOne.GetpositionX());

                if(checkHitbox(playerOne, monsterOne))
                {

                    cout << "There is a hit!" << endl;

                    cout << "Player life: " << playerOne.Getlife();

                    int actualDamages = playerOne.Getdamages() - monsterOne.getArmor();

                    if(actualDamages > 0)
                        monsterOne.setLife(monsterOne.getLife() - actualDamages);

                    if(monsterOne.getLife() <= 0)
                    {

                        playerOne.setGold(playerOne.getGold() + monsterOne.getPrize());

                        //return;

                    }

                    actualDamages = monsterOne.getAttack() - playerOne.Getarmor();

                    if(actualDamages > 0)
                        playerOne.Setlife(playerOne.Getlife() - actualDamages);

                    if(playerOne.Getlife() <= 0)
                    {

                        break;

                    }

                }

                RefreshGameDisplay(screen, playerOne);

                monsterOne.Draw(screen);

                playerOne.Draw(screen);

                break;

            case MENU:

                DisplayMenu(screen);

            default:

                break;

        }

        // finally, update the screen :)
        SDL_Flip(screen);

    } // end main loop

    _sleep(1000);

    DisplayGameOver(screen);

    // finally, update the screen :)
    SDL_Flip(screen);

    _sleep(3000);

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}

void RefreshGameDisplay(SDL_Surface* screen, Player playerOne)
{


    SDL_FreeSurface(screen);

    SDL_Rect rectangle;

    rectangle.x = 0;

    rectangle.y = 0;

    rectangle.w = screen->w;

    rectangle.h = screen->h;

    SDL_FillRect(screen, &rectangle, SDL_MapRGB(screen->format, 0X00, 0X00, 0X00));

    rectangle.y = 80;

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

    int healthBarReference = rectangle.w + SPRITESIZE;

    SDL_FillRect(screen, &rectangle, SDL_MapRGB(screen->format, 0xff, 0xff, 0xff));

    rectangle.x = SPRITESIZE;

    rectangle.y = 10 + SPRITESIZE;

    rectangle.h = SPRITESIZE;

    double lifeSections = (10 * SPRITESIZE) / playerOne.GetMaxLife();

    double percentage = (playerOne.Getlife() * 100) / playerOne.GetMaxLife();

    rectangle.w = (10 * SPRITESIZE) * (percentage/100);

    SDL_FillRect(screen, &rectangle, SDL_MapRGB(screen->format, 0xff, 0x00, 0x00));

    rectangle.x = healthBarReference + 22;

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

void DisplayGameOver(SDL_Surface* screen)
{

    SDL_FreeSurface(screen);

    SDL_Rect rectangle;

    rectangle.x = 0;

    rectangle.y = 0;

    rectangle.w = screen->w;

    rectangle.h = screen->h;

    SDL_Surface* gameOverImage = SDL_LoadBMP("gameOver.bmp");

    SDL_BlitSurface(gameOverImage, 0, screen, &rectangle);

}

void DisplayMenu(SDL_Surface* Screen)
{

    SDL_FreeSurface(Screen);

    SDL_Rect rectangle;

    rectangle.x = 0;

    rectangle.y = 0;

    rectangle.w = Screen->w;

    rectangle.h = Screen->h;

    SDL_Surface* caracMenu = SDL_LoadBMP("caracMenu.bmp");

    SDL_BlitSurface(caracMenu, 0, Screen, &rectangle);


}

bool checkHitbox(Player aPlayer, Monster aMonster)
{

    if(aPlayer.GetpositionX() + aPlayer.GetspriteSize() == aMonster.getPositionX())
        return true;

    if(aPlayer.GetpositionX() == aMonster.getPositionX() + aMonster.getSpriteSize())
        return true;

    return false;

}

void applyDamages(Player aPlayer,Monster aMonster)
{

    int actualDamages = aPlayer.Getdamages() - aMonster.getArmor();

    if(actualDamages > 0)
        aMonster.setLife(aMonster.getLife() - actualDamages);

    if(aMonster.getLife() <= 0)
    {

        aPlayer.setGold(aPlayer.getGold() + aMonster.getPrize());

        return;

    }

    actualDamages = aMonster.getAttack() - aPlayer.Getarmor();

    if(actualDamages > 0)
        aPlayer.Setlife(aPlayer.Getlife() - actualDamages);

}
