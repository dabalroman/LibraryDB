#include "DataKeeper.hpp"
#include "ConsoleRenderer/Console.hpp"
#include "ConsoleRenderer/ConsoleRenderer.hpp"
#include "Screens/ListScreen.hpp"
#include "Screens/DetailsScreen.hpp"

using namespace std;

int main() {
	//Data storage
	DataKeeper dk;
	dk.loadFromFile();

	//Communication with console & renderer
	Console console;
	ConsoleRenderer consoleRenderer(console);

	//Screens
	auto *listScreen = new ListScreen(console, dk);
	auto *details = new DetailsScreen(console, dk);

	//Add screens to renderer
	consoleRenderer.addScreen(listScreen);
	consoleRenderer.addScreen(details);

	//Render first screen
	consoleRenderer.render();

	//App heartbeat
	bool close = false;
	do {
		auto c = console.getKey();

		//Handle screen input
		int returnCode = consoleRenderer.getActiveScreen()->handleInput(c);

		//Exit
		if (returnCode == Screen::EXIT) {
			close = true;
			continue;
		}

		//Set screen
		if (returnCode >= 0) {
			consoleRenderer.setActiveScreen(returnCode);

			//Re-handle input with fake key to update screen content
			c.wVirtualKeyCode = 0;
			consoleRenderer.getActiveScreen()->handleInput(c);
		}

		//Render screen
		consoleRenderer.render();
	} while (!close);

	//Save data
	dk.saveToFile();
	return 0;
}