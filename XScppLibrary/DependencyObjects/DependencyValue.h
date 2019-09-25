#pragma once

#include "Dependency.h"
#include "../Events/EventHandler.h"

namespace XSLibrary
{
	template<class T>
	class DependencyValue : public Dependency, public EventHandler
	{
	public:
		Event<void*, T> ValueChanged;

		DependencyValue();
		DependencyValue(T const& value);

		virtual T GetValue() const;
		virtual void SetValue(T const& value);

	protected:
		T m_value;
	};

	template<class T>
	inline DependencyValue<T>::DependencyValue()
	{
		Subscribe(ValueChanged, [](void * sender, T)
		{
			Changed.Invoke(sender);
		});
	}
	template<class T>
	inline DependencyValue<T>::DependencyValue(T const & value)
		: DependencyValue<T>()
	{
		m_value = value;
	}
	template<class T>
	inline T DependencyValue<T>::GetValue() const
	{
		return m_value;
	}
	template<class T>
	inline void DependencyValue<T>::SetValue(T const & value)
	{
		if (m_value != value)
		{
			m_value = value;
			ValueChanged.Invoke(this, value);
		}
	}
}