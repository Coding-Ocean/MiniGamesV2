#pragma once
#include "ACTOR.h"
#include "INT2.h"
namespace GAME04 {

    class GHOST :
        public ACTOR
    {
    public:
        GHOST(int no, class GAME* game);
        ~GHOST();
        void create();
        void destroy();
        void init();
        void update();
        void draw();
        INT2 pos() { return Pos; }
    private:
        int GetDir();
        void ModeChange();

        int Size;
        float OfstX;
        float OfstY;

        int No;
        int Imgs[4][4][2];
        int ImgFrightened[2][2];
        int ImgEaten[4];
        int AnimCnt;

        int Speed;

        const int DEPARTURE_UPDOWN = 0;
        const int DEPARTURE_TOCENTER = 1;
        const int DEPARTURE = 2;
        const int SCATTER = 3;
        const int CHASE = 4;
        int FrightenedFlag = 0;//ここだけフラッグ！
        const int EATEN = 6;
        const int EATEN_HOME = 7;
        int Mode = SCATTER;

        int UpDownCnt = 0;
        int DepartureCnt[4];
        int ScatterChaseCnt = 0;
        int FrightenedCnt = 0;

        INT2 Pos;
        const int U = 0, L = 1, D = 2, R = 3;
        INT2 DIR[4];
        int DirIdx;

        int SndFrightened;
        int SndEatGhost;
        int SndOver;
    };
}