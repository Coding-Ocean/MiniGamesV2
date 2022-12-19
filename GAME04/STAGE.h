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

        //�ʂ蓹���H
        int pathway(int posx, int posy);
        //�a��H�ׂ�ꂽ
        void eaten(int posx, int posy);
        //�ǂ��H
        int wall(int col, int row);
        //�p���[�a��H�ׂ����H
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