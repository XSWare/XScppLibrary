#include "stdafx.h"
#include "Observer.h"

XSLibrary::Observer::~Observer()
{
	for (auto & entry : m_subscriptions)
		entry.second->Unsubscribe(entry.first);
}
