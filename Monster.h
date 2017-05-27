#include <SDL/SDL.h>

enum MonsterDirection
{

    HALT = 0,

    GAUCHE,

    DROITE,

};

class Monster
{

private:

    int positionX;

    int positionY;

    int life;

    int armor;

    int attack;

    int spriteSize;

    int maxX;

    int minX;

    MonsterDirection direction;

public:

    Monster(SDL_Surface* screen, int likfe, int attack, int armor);

    int getPositionX(){return this->positionX;}

    int getLife(){return this->life;}

    int getArmor(){return this->armor;}

    int getAttack(){return this->attack;}

    MonsterDirection getDirection(){return this->direction;}

    void Draw(SDL_Surface* screen);

    void Update(int playerPOSX);

};
