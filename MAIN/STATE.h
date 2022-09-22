#ifndef STATE_HD
#define STATE_HD

#include"../libOne/inc/graphic.h"
class STATE{
public:
	STATE(class MANAGER* m) { manager = m; }
	virtual ~STATE() { refreshCntnr(); }
	virtual void create() = 0;
	virtual void proc() = 0;
	virtual void destroy() = 0;
protected:
	class MANAGER* manager;
};

#endif