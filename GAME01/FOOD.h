#pragma once
#include "ACTOR.h"
namespace GAME01
{
    class FOOD :
        public ACTOR
    {
    public:
        FOOD(class GAME* game) :ACTOR(game) {}
        ~FOOD() {}
        void init();
        void draw();
    };

}