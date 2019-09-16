#include "AppEngine.hpp"

#include "LoginState.hpp"

int main(int argc, char* argv[])
{
	AppSettings settings;
	settings.launchOptions = { argc, argv };

	AppEngine app;
	app.Init("SFLCARS-AppEngine", settings);

	app.PushState(new LoginState);

	while (app.isRunning())
	{
		app.Update();
		app.HandleEvents();
		app.Draw();
	}

	app.Cleanup();

	return EXIT_SUCCESS;
}
