#include"graphic.h"
#include"input.h"
#include"FADE.h"

FADE::FADE(){
    Speed = 20;
    FadeState = FADE_OUT_END;
}
FADE::~FADE(){
}
void FADE::fadeInTrigger(){
    if( FadeState == FADE_OUT_END )FadeState = FADE_IN_TRIGGER;
}
void FADE::fadeOutTrigger(){
    if( FadeState == FADE_IN_END ) FadeState = FADE_OUT_TRIGGER;
}
void FADE::draw(){
    if( FadeState == FADE_IN_END ){
        return;
    }
    colorMode(RGB);
    rectMode(CORNER);
    stroke(0);
    strokeWeight(1);
    if(      FadeState == FADE_IN_TRIGGER ){
        Alpha = 255;
        fill(0,0,0, Alpha);
        rect(0, 0, width, height);
        FadeState = FADE_IN;
    }
    else if( FadeState == FADE_IN ){
        fill(0, 0, 0, Alpha);
        rect(0, 0, width, height);
        Alpha -= Speed;
        if( Alpha < 0 ){
            FadeState = FADE_IN_END;
        }
    }
    else if( FadeState == FADE_OUT_TRIGGER ){
        Alpha = 0;
        FadeState = FADE_OUT;
    }
    else if( FadeState == FADE_OUT ){
        fill(0, 0, 0, Alpha);
        rect(0, 0, width, height);
        Alpha += Speed;
        if( Alpha >= 255 ){
            Alpha = 255;
            FadeState = FADE_OUT_END;
        }
    }
    else if( FadeState == FADE_OUT_END ){
        fill(0, 0, 0, 255);
        rect(0, 0, width, height);
    }
}
int FADE::fadeInEndFlag() {
    return (FadeState == FADE_IN_END);
}
int FADE::fadeOutEndFlag(){
    return ( FadeState == FADE_OUT_END );
}
void FADE::setSpeed( int speed ){
    Speed = speed;
}

