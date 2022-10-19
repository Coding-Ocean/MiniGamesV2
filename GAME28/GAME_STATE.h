#pragma once
namespace GAME28 {

	class GAME_STATE
	{
	public:
		GAME_STATE(class GAME_MANAGER* m) { manager = m; }
		virtual ~GAME_STATE() {}
		virtual void create() = 0;
		virtual void destroy() = 0;
		virtual void proc() = 0;
	protected:
		class GAME_MANAGER* manager;
	};

}
