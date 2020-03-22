#include "AppEngine.hpp"

#include "InitialiseState.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
	AppSettings settings;
	settings.launchOptions = { argc, argv };

	AppEngine app;
	app.Init(settings);

	app.PushState(new InitialiseState);

	while (app.isRunning())
	{
		app.HandleEvents();
		app.Update();
		app.Draw();
	}

	app.Cleanup();

	return EXIT_SUCCESS;
}
