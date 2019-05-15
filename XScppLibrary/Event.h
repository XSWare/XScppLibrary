#pragma once

#include <functional>
#include <map>

namespace XSLibrary
{
	template <typename... Args>
	struct SelectFunctionType
	{
		using type = std::function<void(Args...)>;
	};
	
	template <typename... Args>
	using Delegate = typename SelectFunctionType<Args...>::type;

	class IEvent
	{
	public:
		virtual void Unsubscribe(int ID) = 0;
	};

	template <typename... Args>
	class Event : public IEvent
	{
	public:
		Event()
		{
			m_nextID = 0;
		}

		int Subscribe(Delegate<Args...> eventHandle);
		virtual void Unsubscribe(int ID) override;
		void Invoke(Args... args);

	private:
		std::map<int, Delegate<Args>> m_subscribers;
		int m_nextID;
	};

	template<typename... Args>
	int Event<Args...>::Subscribe(Delegate<Args...> eventHandle)
	{
		if (m_nextID == -1)
			m_nextID++;

		m_subscribers[m_nextID] = eventHandle;

		return m_nextID++;
	}

	template<typename... Args>
	void Event<Args...>::Unsubscribe(int ID)
	{
		m_subscribers.erase(ID);
	}

	template<typename... Args>
	void Event<Args...>::Invoke(Args... args)
	{
		for (auto & entry : this->m_subscribers)
			entry.second(args);
	}
}