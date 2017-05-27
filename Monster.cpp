#include "Monster.h"

Monster::Monster(SDL_Surface* screen, int life, int attack, int armor)
{

    this->life = life;

    this->armor = armor;

    this->attack = attack;

    this->positionX = (screen->w-60);

    this->positionY = screen->h-40-20;

    this->spriteSize = 40;

    this->minX = 0;

    this->maxX = screen->w - 40;

}

void Monster::Draw(SDL_Surface* screen)
{

    SDL_Rect rectangle;

    rectangle.h = this->spriteSize;

    rectangle.w = this->spriteSize;

    rectangle.x = this->positionX;

    rectangle.y = this->positionY;

    // rend une des couleurs transparente

    //SDL_SetColorKey(hero, SDL_SRCCOLORKEY, SDL_MapRGB(hero->format, 255, 255, 255));

    //SDL_BlitSurface(hero, 0, screen, &rectangle);

    SDL_FillRect(screen, &rectangle, SDL_MapRGB(screen->format, 0xFF, 0X00, 0X00));

}

void Monster::Update(int playerPOSX)
{

    if(playerPOSX < this->positionX - 20)

        this->direction = GAUCHE;

    else if(playerPOSX > this->positionX + 20)

        this->direction = DROITE;

    else

        this->direction = HALT;

    switch(this->direction)
    {

    case GAUCHE:

        if(this->positionX > this->minX)
            this->positionX -= this->spriteSize;

        break;

    case DROITE:

        if(this->positionX < this->maxX - this->spriteSize)
            this->positionX += this->spriteSize;

    default:

        break;

    }

}
