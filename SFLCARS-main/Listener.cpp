#include "Listener.hpp"

Listener::Listener()
{
	selector.add(socket);
}

void Listener::Update()
{
	if (selector.wait(sf::seconds(1.0f)))
	{
		if (selector.isReady(socket))
		{

		}
	}
}
