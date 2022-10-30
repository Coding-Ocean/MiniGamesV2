#pragma once
#include "ACTOR.h"
namespace GAME01
{
    class STAGE :
        public ACTOR
    {
    public:
        STAGE(class GAME* game):ACTOR(game){}
        ~STAGE(){}
        void init();
        void draw();
    private:
        void DrawScore();
        void DrawGameOver();
        float W=0;
        float H=0;
    };

}