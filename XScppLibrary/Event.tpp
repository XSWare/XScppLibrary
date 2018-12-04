template<class T>
EventBase<T>::EventBase()
{
	m_nextID = 0;
}

template<class T>
int EventBase<T>::Subscribe(Delegate<T> eventHandle)
{
	if (m_nextID == INVOKE_ALL)
		m_nextID++;

	m_subscribers[m_nextID] = eventHandle;

	return m_nextID++;
}

template<class T>
void EventBase<T>::Unsubscribe(int ID)
{
	m_subscribers.erase(ID);
}

template<class T>
void Event<T>::Invoke(T param, int invokerID)
{
	for (auto & entry : this->m_subscribers)
	{
		if (entry.first != invokerID)
			entry.second(param);
	}
}

void Event<void>::Invoke(int invokerID)
{
	for (auto & entry : this->m_subscribers)
	{
		if (entry.first != invokerID)
			entry.second();
	}
}
