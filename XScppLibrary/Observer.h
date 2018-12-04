#pragma once

#include "Event.h"
#include <memory>

namespace XSLibrary
{
	class Observer
	{
	public:
		Observer();
		virtual ~Observer();

		template<class T>
		void AddEvent(std::shared_ptr<Event<T>> event_, Delegate<T> action);

	private:
		std::map<int, std::shared_ptr<IEvent>> m_subscriptions;
	};

#include "Observer.tpp"
}