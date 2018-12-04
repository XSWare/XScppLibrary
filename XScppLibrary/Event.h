#pragma once

#include "IEvent.h"
#include <functional>
#include <map>

namespace XSLibrary
{
	const int INVOKE_ALL = -1;

	template <typename T>
	struct SelectFunctionType
	{
		using type = std::function<void(T)>;
	};

	template <>
	struct SelectFunctionType<void>
	{
		using type = std::function<void()>;
	};
	
	template <typename T>
	using Delegate = typename SelectFunctionType<T>::type;

	class IEvent
	{
	public:
		virtual void Unsubscribe(int ID) = 0;
	};

	template <class T>
	class EventBase : public IEvent
	{
	public:
		EventBase();

		int Subscribe(Delegate<T> eventHandle);
		virtual void Unsubscribe(int ID) override;

	protected:
		std::map<int, Delegate<T>> m_subscribers;

	private:
		int m_nextID;
	};

	template <class T>
	class Event : public EventBase<T>
	{
	public:
		void Invoke(T param, int invokerID = INVOKE_ALL);
	};

	template<>
	class Event<void> : public EventBase<void>
	{
	public:
		void Invoke(int invokerID = INVOKE_ALL);
	};

#include "Event.tpp"
}