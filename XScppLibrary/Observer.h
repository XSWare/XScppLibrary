#pragma once

#include "Event.h"
#include <memory>

namespace XSLibrary
{
	class Observer
	{
	public:
		~Observer();

		template<class T>
		void AddEvent(std::shared_ptr<Event<T>> event_, Delegate<T> action);

	private:
		std::map<int, std::shared_ptr<IEvent>> m_subscriptions;
	};

	template<class T>
	inline void Observer::AddEvent(std::shared_ptr<Event<T>> event_, Delegate<T> action)
	{
		int ID = event_->Subscribe(action);
		std::shared_ptr<IEvent> basePtr = std::static_pointer_cast<std::shared_ptr<IEvent>>(event_);
		m_subscriptions[ID] = basePtr;
	}
}