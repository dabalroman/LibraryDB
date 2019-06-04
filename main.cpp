#include <iostream>
#include <iomanip>
#include <windows.h>
#include <cctype>
#include <cstdio>
#include <wincon.h>
#include <conio.h>
#include <sstream>
#include "DataKeeper.hpp"
#include "Utils.hpp"
#include "ConsoleRenderer/Console.hpp"
#include "ConsoleRenderer/TextField.hpp"
#include "ConsoleRenderer/InputField.hpp"
#include "ConsoleRenderer/ConsoleRenderer.hpp"
#include "ConsoleRenderer/DataListRenderable.hpp"
#include "ListScreen.hpp"

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
//	auto *details = new Screen();

	//List screen
//	details->addRenderable(tf);

	consoleRenderer.addScreen(listScreen);
//	consoleRenderer.addScreen(details);
	consoleRenderer.render();

	//App heartbeat
	bool close = false;


	while (!close) {
		auto c = console.getKey();

		close = consoleRenderer.getActiveScreen()->handleInput(c);
		consoleRenderer.render();
	}

	//Save data
	dk.saveToFile();
	return 0;
}