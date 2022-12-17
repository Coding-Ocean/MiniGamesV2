#pragma once
#include "ACTOR.h"
#include "INT2.h"
namespace GAME04 {

    class PLAYER :
        public ACTOR
    {
    public:
        PLAYER(class GAME* game);
        ~PLAYER();
        void create();
        void destroy();
        void init();
        void update();
        void draw();
        INT2 pos() { return Pos; }
    private:
        int Size;
        float OfstX;
        float OfstY;

        int Floor(int pos);

        int Img[3];
        int AnimCnt;
        INT2 Pos;
        INT2 Dir;
        float Angle;
        int Speed;

    };
}