#include "AppEngine.hpp"

#include "InitialiseState.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
	AppSettings settings;
	settings.launchOptions = { argc, argv };

	{
		AppEngine app("SFLCARS-AppEngine", settings);

		app.PushState(new InitialiseState);

		while (app.isRunning())
		{
			app.HandleEvents();
			app.Update();
			app.Draw();
		}
	} // cleanup AppEngine here

	std::cin.get();

	return EXIT_SUCCESS;
}
