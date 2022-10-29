#include "../libOne/inc/sound.h"
#include "GAME.h"
#include "STAGE.h"
#include "SCORE.h"
namespace GAME00
{
	SCORE::SCORE(GAME* game):ACTOR(game){}
	SCORE::~SCORE() {}

	void SCORE::init()
	{
		AiScore = 0;
		PlayerScore = 0;
		CountUpFlag = false;
		TextSize = 100;
		WinScore = 5;
	}

	void SCORE::update()
	{
		float stageH = game()->stage()->h();
		ACTOR* ball = game()->ball();
		//プレイ中
		if (ball->py() > 0 && 
			ball->py() < stageH) {
			CountUpFlag = false;
		}
		//一度点数をカウントアップしたら再プレイまでここには入らない
		if (CountUpFlag == false) {
			if (ball->py() < -100) {
				CountUpFlag = true;
				PlayerScore++;
				if (PlayerScore >= WinScore) {
					playSound(game()->winSnd);
				}
				else {
					playSound(game()->pointSnd);
				}
			}
			else if (ball->py() > stageH + 100) {
				CountUpFlag = true;
				AiScore++;
				if (AiScore >= WinScore) {
					playSound(game()->loseSnd);
				}
				else {
					playSound(game()->pointSnd);
				}
			}
		}
	}

	void SCORE::DrawScore(int score, float py)
	{
		float ofstX = 0;
		if (score >= 10)
			ofstX = 130; 
		else 
			ofstX = 80;
		textSize(100);
		text(score, game()->stage()->px() - ofstX, py);
	}

	void SCORE::DrawResult(const char* msg)
	{
		game()->gameSet();

		float stageW = game()->stage()->w();
		float stageH = game()->stage()->h();
		float ofstX = game()->stage()->px();

		fill(255, 255, 0);
		size_t len = strlen(msg);
		textSize(TextSize);
		float px = ofstX + (stageW - TextSize/2 * len) / 2 + TextSize/4;
		text(msg, px, stageH / 2);
		
		msg = "Push [R] to replay";
		len = strlen(msg);
		float size = TextSize * 0.3f;
		textSize(size);
		px = ofstX + (stageW - size/2 * len) / 2;
		text(msg, px, stageH / 2 + TextSize*0.8f);
	}

	void SCORE::draw()
	{
		fill(200);
		textMode(BCENTER);
		DrawScore(AiScore, 270);
		DrawScore(PlayerScore, 810);
		//Result
		if (AiScore >= WinScore) {
			DrawResult("You Lose!");
		}
		else if (PlayerScore >= WinScore) {
			DrawResult("You Win!");
		}
	}
}