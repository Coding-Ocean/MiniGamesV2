#pragma once
#include<vector>
#include "ACTOR.h"
namespace GAME01
{
    class SNAKE :
        public ACTOR
    {
    public:
        SNAKE(class GAME* game) :ACTOR(game) {}
        ~SNAKE() {}
        void init();
        void update();
        void draw();
        void input();
        class PARTS {
        public:
            PARTS(int col, int row) { Col = col; Row = row; }
            int col() { return Col; }
            int row() { return Row; }
            friend class SNAKE;
        private:
            int Col = 0;
            int Row = 0;
        };
        std::vector<PARTS>& parts() { return Parts; };
        int length() { return (int)Parts.size(); }
    private:
        int Dx=0, Dy=0;
        std::vector<PARTS>Parts;
    };

}