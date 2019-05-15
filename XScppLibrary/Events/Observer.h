#pragma once

#include "Event.h"

namespace XSLibrary
{
	class Observer
	{
	public:
		template<typename... Args>
		void AddEvent(Event<Args...> & event_, Delegate<Args...> action);

	private:
		std::vector<Subscription> m_subscriptions;
	};

	template<typename ...Args>
	void Observer::AddEvent(Event<Args...> & event_, Delegate<Args...> action)
	{
		m_subscriptions.push_back(event_.Subscribe(action));
	}
}