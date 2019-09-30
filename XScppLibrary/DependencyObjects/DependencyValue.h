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
		virtual void SetValue(T const& value, void * sender = nullptr);

		void operator=(T const& value);
		bool operator==(T const& value) const;
		bool operator!=(T const& value) const;

	protected:
		T m_value;
	};

	template<class T>
	inline DependencyValue<T>::DependencyValue()
	{
		Subscribe(ValueChanged, [this](void * sender, T)
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
	inline void DependencyValue<T>::SetValue(T const & value, void * sender)
	{
		if (m_value != value)
		{
			m_value = value;
			ValueChanged.Invoke(sender ? sender : this, value);
		}
	}

	template<class T>
	inline void DependencyValue<T>::operator=(T const & value)
	{
		SetValue(value);
	}

	template<class T>
	inline bool DependencyValue<T>::operator==(T const & value) const
	{
		return GetValue() == value;
	}

	template<class T>
	inline bool DependencyValue<T>::operator!=(T const & value) const
	{
		return !(*this == value);
	}
}