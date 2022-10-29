#pragma once
#include "ACTOR.h"
namespace GAME00
{
	class BALL : 
		public ACTOR
	{
	public:
		BALL(class GAME* game);
		void init();
		void update();
		void draw();
	private:
		void Collision();
		bool PlaySoundOnce;
	};

}