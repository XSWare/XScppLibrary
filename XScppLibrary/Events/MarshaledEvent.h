#pragma once

#include "Event.h"
#include <map>

namespace XSLibrary
{

	template <typename IDType, typename... Args>
	class MarshaledEvent : public Event<Args...>
	{
	private:
		static std::map<IDType, Event<Args...> &> m_lookup;

		bool m_registered;
		IDType m_id;

	public:
		typedef void(__cdecl *DelegateSignature) (IDType, Args...);

		MarshaledEvent()
		{
			m_registered = false;
		}

		virtual ~MarshaledEvent()
		{
			if (m_registered)
				m_lookup.erase(m_id);
		}
		void Register(IDType id)
		{
			if (m_registered)
				return;

			m_registered = true;
			m_id = id;
			m_lookup.insert(std::pair<IDType, Event<Args...> &>(id, *this));
		}

		DelegateSignature GetCallback()
		{
			return &MarshaledEvent<IDType, Args...>::InvokeMarshaled;
		}

		static void InvokeMarshaled(IDType id, Args... args)
		{
			auto & entry = m_lookup.find(id);
			if (entry != m_lookup.end())
				entry->second.Invoke(args...);
		}
	};

	template <typename IDType, typename... Args>
	std::map<IDType, Event<Args...> &> MarshaledEvent<IDType, Args...>::m_lookup;

}