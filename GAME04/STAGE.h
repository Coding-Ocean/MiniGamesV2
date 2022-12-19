#pragma once
#include "ACTOR.h"
namespace GAME04 {

    class STAGE :
        public ACTOR
    {
    public:
        STAGE(class GAME* game);
        ~STAGE();
        void create();
        void destroy();
        void init();
        void update();
        void draw();

        void drawWarpZone();
        void drawStageClear();

        //通り道か？
        int pathway(int posx, int posy);
        //餌を食べられた
        void eaten(int posx, int posy);
        //壁か？
        int wall(int col, int row);
        //パワー餌を食べたか？
        int powerFoodEaten() { return PowerFoodEaten; }

        int size() { return Size; }
        float ofstX() { return OfstX; }
        float ofstY() { return OfstY; }
    private:
        int Img_a;
        int Img_b;
        int Img_c;
        int Img_d;
        int Img_x;
        int Img_y;

        int Rows;
        int Cols;
        char* Map;

        int Size;//Chip size
        float OfstX;
        float OfstY;

        int NumFood;
        int PowerFoodEaten;

        int SndOpenning;
        int SndEat;
        int SndFrightened;
        int SndClear;
    };

}