#include "../libOne/inc/graphic.h"
#include "../libOne/inc/rand.h"
#include "GAME.h"
#include "STAGE.h"
#include "SNAKE.h"
#include "FOOD.h"
namespace GAME01
{
	void FOOD::init()
	{
		Scale = game()->stage()->scale();
		int maxCol = game()->stage()->col();
		int maxRow = game()->stage()->row();

		std::vector<SNAKE::PARTS>& parts
			= game()->snake()->parts();
		
		int duplicated = 0;
		do {
			Col = random() % maxCol;
			Row = random() % maxRow;
			duplicated = 0;
			for (size_t i = 0; i < parts.size(); i++) {
				if (Col == parts[i].col() &&
					Row == parts[i].row()) {
					duplicated = 1;
				}
			}
		} while (duplicated);
	}
	void FOOD::draw()
	{
		float ox = game()->stage()->px() + Scale/2;
		float oy = game()->stage()->py() + Scale/2;
		Px = ox + Scale * Col;
		Py = oy + Scale * Row;
		fill(255,0,255);
		stroke(255, 0, 0);
		strokeWeight(Scale * 0.3f);
		circle(Px, Py, Scale*0.5f);
	}
}