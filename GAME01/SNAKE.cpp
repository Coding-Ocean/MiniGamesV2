#include "../libOne/inc/graphic.h"
#include "../libOne/inc/rand.h"
#include "../libOne/inc/input.h"
#include "../libOne/inc/mathUtil.h"
#include "../libOne/inc/sound.h"
#include "GAME.h"
#include "STAGE.h"
#include "FOOD.h"
#include "SNAKE.h"
namespace GAME01
{
	void SNAKE::init()
	{
		Scale = game()->stage()->scale();
		Col = 0;
		Row = 0;
		Dx = 1;
		Dy = 0;
		Parts.clear();
		Parts.emplace_back(Col, Row);
	}
	void SNAKE::input()
	{
		if      (isTrigger(KEY_D)) { Dx = 1; Dy = 0; }
		else if (isTrigger(KEY_A)) { Dx = -1; Dy = 0; }
		else if (isTrigger(KEY_W)) { Dx = 0; Dy = -1; }
		else if (isTrigger(KEY_S)) { Dx = 0; Dy = 1; }
	}
	void SNAKE::update()
	{
		Col += Dx;
		Row += Dy;
		//ワープ
		int maxCol = game()->stage()->col() - 1;
		int maxRow = game()->stage()->row() - 1;
		if (Col < 0)Col = maxCol;
		if (Col > maxCol)Col = 0;
		if (Row < 0)Row = maxRow;
		if (Row > maxRow)Row = 0;
		//自分を食べたらゲームオーバー
		for (size_t i = 0; i < Parts.size(); i++) {
			if (Col == Parts[i].Col &&
				Row == Parts[i].Row) {
				game()->toGameOver();
				playSound(game()->gameOverSnd);
			}
		}
		//食べる
		if (Col == game()->food()->col() &&
			Row == game()->food()->row()) {
			Parts.emplace_back(Col, Row);
			game()->food()->init();
			playSound(game()->eatSnd);
		}
		else {
			//進む
			size_t i=0;
			for (i = 0; i < Parts.size() - 1; i++) {
				Parts[i] = Parts[i + 1];
			}
			Parts[i].Col = Col;
			Parts[i].Row = Row;
		}
	}
	void SNAKE::draw()
	{
		float ox = game()->stage()->px() + Scale / 2;
		float oy = game()->stage()->py() + Scale / 2;
		float strokeW = Scale * 0.2f;
		float divColor = 64.0f / Parts.size();
		float maxScale = Scale * 0.7f;
		float minScale = maxScale * 0.5f;
		float divScale = minScale / Parts.size();
		rectMode(CENTER);
		angleMode(DEGREES);
		for (size_t i = 0; i < Parts.size(); i++) {
			Px = ox + Scale * Parts[i].Col;
			Py = oy + Scale * Parts[i].Row;
			COLOR strokeColor(0, 192 + divColor * (i + 1), 0);
			float scale = minScale + divScale * (i + 1);
			if (i < Parts.size() - 1) {
				fill(255, 255, 0);
				stroke(strokeColor);
				strokeWeight(strokeW);
				rect(Px, Py, scale, scale, 45);
			}
			else {
				//ベロの準備（ついでに目も準備）
				float  tongueX = 0, tongueY = 0;
				float eyeX1 = 0, eyeX2 = 0, eyeY1 = 0, eyeY2 = 0;
				float rnd1 = random(Scale * 0.5f, Scale * 1.0f);
				float rnd2 = random(-2.0f, 2.0f);
				float ofst = Scale * 0.2f;
				if (Dx) {
					tongueX = Dx * rnd1; tongueY = rnd2;
					eyeX1 = px() + Dx * ofst; eyeX2 = px() + Dx * ofst;
					eyeY1 = py() - ofst; eyeY2 = py() + ofst;
				}
				else if (Dy) {
					tongueX = rnd2; tongueY = Dy * rnd1;
					eyeX1 = px() - ofst; eyeX2 = px() + ofst;
					eyeY1 = py() + Dy * ofst; eyeY2 = py() + Dy * ofst;
				}
				//ベロ
				stroke(255, 0, 0);
				strokeWeight(Scale * 0.1f);
				line(px(), py(), px() + tongueX, py() + tongueY);
				//頭
				fill(strokeColor);
				stroke(strokeColor);
				strokeWeight(strokeW);
				rect(Px, Py, scale, scale, 45);
				//目
				stroke(0);
				strokeWeight(Scale * 0.2f);
				point(eyeX1, eyeY1);
				point(eyeX2, eyeY2);
			}
		}
	}
}