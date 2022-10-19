#include<fstream>
#include"../libOne/inc/libOne.h"
#include"../MAIN/MANAGER.h"
#include"../MAIN/FADE.h"
#include"../GAME00/GAME.h"
#include"../GAME01/GAME.h"
#include"../GAME02/GAME.h"
#include"../GAME03/GAME.h"
#include"../GAME04/GAME.h"
#include"../GAME05/GAME.h"
#include"../GAME06/GAME.h"
#include"../GAME07/GAME.h"
#include"../GAME08/GAME.h"
#include"../GAME09/GAME.h"
#include"../GAME10/GAME.h"
#include"../GAME11/GAME.h"
#include"../GAME12/GAME.h"
#include"../GAME13/GAME.h"
#include"../GAME14/GAME.h"
#include"../GAME15/GAME.h"
#include"../GAME16/GAME.h"
#include"../GAME17/GAME.h"
#include"../GAME18/GAME.h"
#include"../GAME19/GAME.h"
#include"../GAME20/GAME.h"
#include"../GAME21/GAME.h"
#include"../GAME22/GAME.h"
#include"../GAME23/GAME.h"
#include"../GAME24/GAME.h"
#include"../GAME25/GAME.h"
#include"../GAME26/GAME.h"
#include"../GAME27/GAME.h"
#include"../GAME28/GAME.h"
#include"../GAME29/GAME.h"
#include"MENU.h"

MENU::MENU(MANAGER* manager)
    :STATE(manager)
{
}

MENU::~MENU(){
}

void MENU::create() {
    ClearImg = loadImage("assets/MENU/clear.png");

    Tate = 5;
    Yoko = 6;
    RectWidth = 250.0f;
    RectHeight = 120.0f;
    
    OfstX = (width - RectWidth * Yoko) / 2;
    OfstY = (height - RectHeight * Tate) / 2;

    NumGames = Tate * Yoko;
    Hue = 360.0f / NumGames;
    Satu = 50;
    Valu = 100;

    //半角18文字x3行までタイトルとして表示できる
    std::ifstream ifs;
    const int buffer_size = 128;
    char buffer[buffer_size];
    int number = 0;
    Titles.clear();
    while (number < NumGames) {
        sprintf_s(buffer, buffer_size, "assets/GAME%02d/title.txt", number);
        ifs.open(buffer);
        if (ifs) {
            TITLE_LINES title;
            int idx = 0;
            while(ifs.getline(buffer, buffer_size) && idx<3){
                 title.lines[idx] = buffer;
                 idx++;
            }
            Titles.push_back(title);
            ifs.close();
        }
        number++;
    }

    //フェードインスタート
    manager->fade->fadeInTrigger();
}

void MENU::destroy()
{

}

void MENU::proc(){
    char& selectIdx = manager->selectIdx; //名前を短くする

    //WASDキー、または、矢印キーでゲームを選択する
    if (isTrigger(KEY_D) || isTrigger(KEY_RIGHT)) {
        selectIdx++;
        if (selectIdx >= NumGames) {
            selectIdx = 0;
        }
    }
    if (isTrigger(KEY_A) || isTrigger(KEY_LEFT)) {
        selectIdx--;
        if (selectIdx < 0) {
            selectIdx = NumGames - 1;
        }
    }
    if (isTrigger(KEY_S) || isTrigger(KEY_DOWN)) {
        selectIdx += Yoko;
        if (selectIdx >= NumGames) {
            selectIdx = selectIdx - (NumGames - 1);
            if (selectIdx == Yoko) {
                selectIdx = 0;
            }
        }
    }
    if (isTrigger(KEY_W) || isTrigger(KEY_UP)) {
        selectIdx -= Yoko;
        if (selectIdx < 0) {
            selectIdx = selectIdx + (NumGames - 1);
            if (selectIdx == (NumGames - 1) - Yoko) {
                selectIdx = (NumGames - 1);
            }
        }
    }
    //マウスで選択
    float left = OfstX;
    float right = OfstX + RectWidth * Yoko;
    float top = OfstY;
    float bottom = OfstY + RectHeight * Tate;
    if (mouseX > left && mouseX<right && mouseY>top && mouseY < bottom) {
        int yoko = int((mouseX - OfstX) / RectWidth);
        int tate = int((mouseY - OfstY) / RectHeight);
        selectIdx = yoko + tate * Yoko;
        if (isTrigger(MOUSE_LBUTTON)) {
            manager->fade->fadeOutTrigger();
        }
    }

    //メニュータイル表示。選択されているところは明るく
    clear(0,0,0);
    colorMode(HSV,100);
    angleMode(DEGREES);
    rectMode(CORNER);
    textMode(TOP);
    textSize(RectWidth/10);
    for( int i = 0; i < Tate; i++ ){
        for( int j = 0; j < Yoko; j++ ){
            //表示位置
            float px = OfstX + RectWidth * j;
            float py = OfstY + RectHeight * i;
            //タイトル
            int k = i * Yoko + j;
            Valu = 60;
            if( k == selectIdx ){
                Valu = 100;
            }
            strokeWeight(10);
            stroke(0);
            fill(Hue*k,Satu,Valu);
            rect(px, py, RectWidth, RectHeight);
            //テキスト
            fill(0, 0, 100);
            if (k == selectIdx) {
                fill(0);
            }
            for (int l = 0; l < 3; l++) {
                text(Titles[k].lines[l].c_str(), px + 10, py + 10 + (RectWidth / 10) * l);
            }
            //クリアチェック画像
            if( manager->clearFlags[ k ] ){
                image(ClearImg, px, py);
            }
        }
    }

    manager->fade->draw();

    //選択されたゲームを呼び出す
    if( isTrigger( KEY_ENTER ) ){
        manager->fade->fadeOutTrigger();
    }
    if( manager->fade->fadeOutEndFlag() ){
        switch (selectIdx) {
        case  0: manager->nextState = new GAME00::GAME(manager); break;
        case  1: manager->nextState = new GAME01::GAME(manager); break;
        case  2: manager->nextState = new GAME02::GAME(manager); break;
        case  3: manager->nextState = new GAME03::GAME(manager); break;
        case  4: manager->nextState = new GAME04::GAME(manager); break;
        case  5: manager->nextState = new GAME05::GAME(manager); break;
        case  6: manager->nextState = new GAME06::GAME(manager); break;
        case  7: manager->nextState = new GAME07::GAME(manager); break;
        case  8: manager->nextState = new GAME08::GAME(manager); break;
        case  9: manager->nextState = new GAME09::GAME(manager); break;
        case 10: manager->nextState = new GAME10::GAME(manager); break;
        case 11: manager->nextState = new GAME11::GAME(manager); break;
        case 12: manager->nextState = new GAME12::GAME(manager); break;
        case 13: manager->nextState = new GAME13::GAME(manager); break;
        case 14: manager->nextState = new GAME14::GAME(manager); break;
        case 15: manager->nextState = new GAME15::GAME(manager); break;
        case 16: manager->nextState = new GAME16::GAME(manager); break;
        case 17: manager->nextState = new GAME17::GAME(manager); break;
        case 18: manager->nextState = new GAME18::GAME(manager); break;
        case 19: manager->nextState = new GAME19::GAME(manager); break;
        case 20: manager->nextState = new GAME20::GAME(manager); break;
        case 21: manager->nextState = new GAME21::GAME(manager); break;
        case 22: manager->nextState = new GAME22::GAME(manager); break;
        case 23: manager->nextState = new GAME23::GAME(manager); break;
        case 24: manager->nextState = new GAME24::GAME(manager); break;
        case 25: manager->nextState = new GAME25::GAME(manager); break;
        case 26: manager->nextState = new GAME26::GAME(manager); break;
        case 27: manager->nextState = new GAME27::GAME(manager); break;
        case 28: manager->nextState = new GAME28::GAME(manager); break;
        case 29: manager->nextState = new GAME29::GAME(manager); break;
        }
    }
}