#include <iostream>
#include <windows.h>
#include <cctype>
#include <cstdio>
#include <wincon.h>
#include <conio.h>
#include "DataKeeper.hpp"
#include "Utils.hpp"

using namespace std;
HANDLE hIn, hOut;

KEY_EVENT_RECORD getKey() {
	DWORD mode, count;
	INPUT_RECORD inputRecord;

	GetConsoleMode(hIn, &mode);
	SetConsoleMode(hIn, 0);
	FlushConsoleInputBuffer(hIn);

	do {
		ReadConsoleInput(hIn, &inputRecord, 1, &count);
	} while (inputRecord.EventType != KEY_EVENT || !inputRecord.Event.KeyEvent.bKeyDown);

	SetConsoleMode(hIn, mode);

	return inputRecord.Event.KeyEvent;
}

int main() {

	DataKeeper dk;

	if (!dk.loadFromFile()) {
		cout << "File access error!";
		_getch();
		return 1;
	}

	for (auto r : dk.records) {
		cout << r->getName() << endl;
	}

	dk.saveToFile();

//	hIn = GetStdHandle(STD_INPUT_HANDLE);
//	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//
//#pragma clang diagnostic push
//#pragma clang diagnostic ignored "-Wmissing-noreturn"
//	while (true) {
//		auto c = getKey();
//		cout << c.uChar.AsciiChar << " (" << (int) c.uChar.AsciiChar << " / " << c.wVirtualKeyCode << ")" << endl
//		     << flush;
//	}
//#pragma clang diagnostic pop

//	_getch();
	return 0;
}