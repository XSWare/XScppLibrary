template<class T>
void Observer::AddEvent(std::shared_ptr<Event<T>> event_, Delegate<T> action)
{
	int ID = event_->Subscribe(action);
	std::shared_ptr<IEvent> basePtr = std::static_pointer_cast<IEvent>(event_);
	m_subscriptions[ID] = basePtr;
}