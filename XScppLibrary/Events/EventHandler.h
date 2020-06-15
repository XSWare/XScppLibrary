#pragma once

#include "Event.h"
#include <map>

namespace XSLibrary
{
	class EventHandler
	{
	public:
		template<typename... Args>
		void Subscribe(Event<Args...>& event_, Delegate<Args...> action);
		template<typename... Args>
		void Relay(Event<Args...>& event_, Event<Args...>& relay);
		template<typename... Args>
		void Unsubscribe(Event<Args...>& event_);

	private:
		std::map<void*, Subscription> m_subscriptions;
	};

	template<typename ...Args>
	inline void EventHandler::Subscribe(Event<Args...>& event_, Delegate<Args...> action)
	{
		m_subscriptions[&event_] = event_.Subscribe(action);
	}

	template<typename ...Args>
	inline void EventHandler::Relay(Event<Args...>& event_, Event<Args...>& relay)
	{
		Subscribe(event_, [&relay](Args... args)
			{
				relay.Invoke(args...);
			});
	}

	template<typename ...Args>
	inline void EventHandler::Unsubscribe(Event<Args...>& event_)
	{
		m_subscriptions.erase(&event_);
	}
}