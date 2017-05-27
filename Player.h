#include <SDL/SDL.h>
#define PLAYERSIZE 40

#define HEROPICTURE "trueHero.bmp"

enum Direction
{

    STOP = 0,

    LEFT,

    RIGHT,

};

class Player
{
    public:

        Player(SDL_Surface* screen);

        int Getlife() { return life; }

        void Setlife(int val) { life = val; }

        int Getdamages() { return damages; }

        void Setdamages(int val) { damages = val; }

        int Getarmor() { return armor; }

        void Setarmor(int val) { armor = val; }

        int GetpositionX() { return positionX; }

        void SetpositionX(int val) { positionX = val; }

        int GetpositionY() { return positionY; }

        void SetpositionY(int val) { positionY = val; }

        int GetspriteSize() { return spriteSize; }

        void SetspriteSize(int val) { spriteSize = val; }

        int GetMaxLife() { return maxLife;}

        void Draw(SDL_Surface* screen);

        void Update(SDLKey pressedKey);

    protected:

    private:
        int maxLife;
        int life;
        int damages;
        int armor;
        int positionX;
        int positionY;
        int maxX;
        int minX;
        int spriteSize;
        Direction direction;
};
