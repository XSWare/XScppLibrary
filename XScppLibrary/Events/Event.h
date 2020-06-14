#pragma once

#include <functional>
#include <vector>
#include <memory>

namespace XSLibrary
{
	template <typename... Args>
	struct SelectFunctionType
	{
		using type = std::function<void(Args...)>;
	};
	
	template <typename... Args>
	using Delegate = typename SelectFunctionType<Args...>::type;

	class Subscription
	{
	public:
		Subscription()
		{
			Unsubscribe();
		}

		Subscription(std::shared_ptr<void> && delegatePointer)
			: m_delegatePointer(std::move(delegatePointer))
		{
		}

		void Unsubscribe()
		{
			m_delegatePointer = nullptr;
		}

	private:
		std::shared_ptr<void> m_delegatePointer;
	};

	template <typename... Args>
	class Event
	{
	public:
		Subscription Subscribe(Delegate<Args...> eventHandle);
		void Invoke(Args... args);

		Subscription operator += (Delegate<Args...> eventHandle);
		void operator() (Args... args);

	private:
		std::vector<std::weak_ptr<Delegate<Args...>>> m_subscribers;
	};

	template<typename ...Args>
	Subscription Event<Args...>::Subscribe(Delegate<Args...> eventHandle)
	{
		std::shared_ptr<Delegate<Args...>> delegatePointer = std::make_shared<Delegate<Args...>>(eventHandle);

		this->m_subscribers.push_back(delegatePointer);

		return Subscription(std::move(delegatePointer));
	}

	template<typename... Args>
	void Event<Args...>::Invoke(Args... args)
	{	
		for (auto it = this->m_subscribers.begin(); it < this->m_subscribers.end();)
		{
			if (auto sharedDelegatePointer = it->lock())
			{
				(*sharedDelegatePointer)(args...);
				it++;
			}
			else
				it = this->m_subscribers.erase(it);
		}
	}

	template<typename... Args>
	Subscription Event<Args...>::operator+=(Delegate<Args...> eventHandle)
	{
		return Subscribe(eventHandle);
	}

	template<typename... Args>
	void Event<Args...>::operator()(Args... args)
	{
		Invoke(args...);
	}
}