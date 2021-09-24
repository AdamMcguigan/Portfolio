#pragma once

namespace gpp
{
	class Events
	{
	public:
		Events();
		~Events();

		enum class Event
		{
			NONE,
			IDLE,
			CHECK_DAGGER,
			DOUBLE_JUMP,
			COUNT
		};

		void setCurrent(Event);
		Event getCurrent();

	private:
		Event m_current;

	};
}