#pragma once

#include "../Events/Event.h"

namespace XSLibrary
{
	class Dependency
	{
	public:
		Event<void*> Changed;
	};
}