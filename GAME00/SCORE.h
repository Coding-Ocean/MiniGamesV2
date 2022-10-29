#pragma once
#include "ACTOR.h"
namespace GAME00
{
    class SCORE :
        public ACTOR
    {
    public:
        SCORE(class GAME* game);
        ~SCORE();
        void init();
        void update();
        void draw();
    private:
        void DrawScore(int score, float py);
        void DrawResult(const char* msg);
        int AiScore;
        int PlayerScore;
        bool CountUpFlag;
        int WinScore;
        float TextSize;
    };
}