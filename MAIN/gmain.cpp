#include "libOne.h"
#include "MANAGER.h"

void gmain() {
	window(1920, 1080, full);

	MANAGER manager;

	while (msgProc()) {
		manager.proc();
	}
}
