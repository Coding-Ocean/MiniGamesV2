#pragma once
#include "ACTOR.h"
namespace GAME00
{
    class PLAYER :
        public ACTOR
    {
    public:
        PLAYER(class GAME* game);
        ~PLAYER();
        void init();
        void update();
        void draw();
    };
}