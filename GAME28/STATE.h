#pragma once
#include"MANAGER.h"
namespace GAME28 {

	class STATE
	{
	public:
		STATE(class MANAGER* manager):_Manager(manager){}
		virtual ~STATE() {}
		virtual void create() = 0;
		virtual void destroy() = 0;
		virtual void proc() = 0;
	protected:
		class MANAGER* Manager() { return _Manager; }
		class GAME* Game() { return _Manager->game(); }
	private:
		class MANAGER* _Manager;
	};

}
