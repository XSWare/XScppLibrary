#pragma once

namespace XSLibrary
{
	class IEvent
	{
	public:
		virtual void Unsubscribe(int ID) = 0;
	};

	class EventBase : IEvent
	{
	public:
		virtual void Unsubscribe(int ID) override {}
	};
}