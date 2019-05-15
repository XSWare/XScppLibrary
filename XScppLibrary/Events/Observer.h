#pragma once

#include "Event.h"
#include <memory>

namespace XSLibrary
{
	class Observer
	{
	public:
		virtual ~Observer()
		{
			for (auto & entry : m_subscriptions)
				entry.second->Unsubscribe(entry.first);
		}

		template<typename... Args>
		void AddEvent(std::shared_ptr<Event<Args...>> event_, Delegate<Args...> action);

	private:
		std::map<int, std::shared_ptr<IEvent>> m_subscriptions;
	};

	template<typename ...Args>
	void Observer::AddEvent(std::shared_ptr<Event<Args...>> event_, Delegate<Args...> action)
	{
		int ID = event_->Subscribe(action);
		std::shared_ptr<IEvent> basePtr = std::static_pointer_cast<IEvent>(event_);
		m_subscriptions[ID] = basePtr;
	}
}