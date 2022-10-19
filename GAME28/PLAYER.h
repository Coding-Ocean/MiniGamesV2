#pragma once
namespace GAME28 {

	class PLAYER
	{
		float Px, Py, Vx;
	public:
		void create();
		void update();
		void draw();
		float px() { return Px; }
	};

}