#pragma once
#include "ACTOR.h"
namespace GAME00
{
    class STAGE :
        public ACTOR
    {
    public:
        STAGE(class GAME* game);
        ~STAGE();
        void init();
        void draw();
    };

}

