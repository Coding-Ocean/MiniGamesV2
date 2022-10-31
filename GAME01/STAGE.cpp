#include "../libOne/inc/graphic.h"
#include "GAME.h"
#include "SNAKE.h"
#include "STAGE.h"
namespace GAME01
{
	void STAGE::init()
	{
		Scale = 100;
		Col = 5;
		Row = 9;
		W = Scale * Col;
		H = Scale * Row;
		Px = (width - W) / 2;
		Py = (height - H) / 2 + 50;
	}
	void STAGE::draw()
	{
		rectMode(CORNER);
		fill(0);
		stroke(0);
		strokeWeight(Scale * 0.2f);
		rect(Px, Py, W, H);
		DrawScore();
		if (game()->gameOver()) {
			DrawGameOver();
		}
	}
	void STAGE::DrawScore()
	{
		textSize(W / 6);
		textMode(BOTTOM);
		fill(0, 255, 0);
		text(game()->snake()->length(), px(), py() - scale() * 0.2f);
	}
	void STAGE::DrawGameOver()
	{
		fill(255, 0, 0);
		text("   GameOver", px(), py() - scale() * 0.2f);
	}
}