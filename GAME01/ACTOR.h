#pragma once
namespace GAME01
{
	class ACTOR
	{
	public:
		ACTOR(class GAME* game):Game(game){}
		virtual ~ACTOR() { Game = 0; }
		virtual void init(){}
		virtual void update(){}
		virtual void draw(){}
		class GAME* game() { return Game; }
		int col() { return Col; }
		int row() { return Row; }
		float px() { return Px; }
		float py() { return Py; }
		float scale() { return Scale; }
	private:
		class GAME* Game=0;
	protected:
		int Col=0, Row=0;
		float Px=0, Py=0;
		float Scale=0;
	};

}