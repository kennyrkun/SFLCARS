#include "AppEngine.hpp"

#include "InitialiseState.hpp"

int main(int argc, char* argv[])
{
	AppSettings settings;
	settings.launchOptions = { argc, argv };

	AppEngine app;
	app.Init("SFLCARS-AppEngine", settings);

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
