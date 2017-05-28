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

    int prize;

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

    Monster(SDL_Surface* screen, int life, int attack, int armor);

    int getPrize(){return this->prize;}

    void setPrize(int prize){this->prize = prize;}

    int getPositionX(){return this->positionX;}

    int getLife(){return this->life;}

    void setLife(int life){ this->life = life;}

    int getArmor(){return this->armor;}

    int getAttack(){return this->attack;}

    int getSpriteSize(){return this ->spriteSize;}

    MonsterDirection getDirection(){return this->direction;}

    void Draw(SDL_Surface* screen);

    void Update(int playerPOSX);

};
