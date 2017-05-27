#include "Player.h"

SDL_Surface* hero = SDL_LoadBMP(HEROPICTURE);

Player::Player(SDL_Surface* screen)
{

    this->maxLife = 10;

    this->life = 10;

    this->armor = 0;

    this->damages = 1;

    this->positionX = 5*(screen->w/PLAYERSIZE);

    this->positionY = screen->h-60;

    this->spriteSize = PLAYERSIZE;

    this->minX = 0;

    this->maxX = screen->w;

}

void Player::Draw(SDL_Surface* screen)
{

    SDL_Rect rectangle;

    rectangle.h = this->spriteSize;

    rectangle.w = this->spriteSize;

    rectangle.x = this->positionX;

    rectangle.y = this->positionY;

    SDL_BlitSurface(hero, 0, screen, &rectangle);

}

void Player::Update(SDLKey pressedKey)
{

    if(pressedKey == SDLK_a)

        this->direction = LEFT;

    else if(pressedKey == SDLK_d)

        this->direction = RIGHT;

    else

        this->direction = STOP;

    switch(this->direction)
    {

    case LEFT:

        if(this->positionX > this->minX)
            this->positionX -= this->spriteSize;

        break;

    case RIGHT:

        if(this->positionX < this->maxX - this->spriteSize)
            this->positionX += this->spriteSize;

    default:

        break;

    }

}
