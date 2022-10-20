#pragma once
#include"../libOne/inc/graphic.h"
#include"MANAGER.h"
namespace MAIN {

	class STATE {
	public:
		STATE(class MANAGER* manager) { _Manager = manager; }
		virtual ~STATE() { refreshCntnr(); }
		virtual void create() = 0;
		virtual void proc() = 0;
		virtual void destroy() = 0;
	protected:
		class MANAGER* Manager() { return _Manager; }
		class FADE* Fade() { return _Manager->fade(); }
	private:
		class MANAGER* _Manager;
	};
}
