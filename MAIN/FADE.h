#pragma once
namespace MAIN {

    class FADE {
    public:
        FADE();
        ~FADE();
        void fadeInTrigger();
        void fadeOutTrigger();
        void draw();
        int fadeOutEndFlag();
        int fadeInEndFlag();
        void setSpeed(int speed);
    private:
        enum FADE_STATE {
            FADE_IN_TRIGGER, FADE_IN, FADE_IN_END,
            FADE_OUT_TRIGGER, FADE_OUT, FADE_OUT_END
        };
        FADE_STATE FadeState;
        int BlackImg;
        int Alpha;
        int Speed;
    };

}