#include "Observer.h"

namespace XSLibrary
{
	Observer::~Observer()
	{
		for (auto & entry : m_subscriptions)
			entry.second->Unsubscribe(entry.first);
	}
}
