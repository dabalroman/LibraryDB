#include <iostream>
#include <windows.h>
#include <cctype>
#include <cstdio>
#include <wincon.h>
#include "DataKeeper.hpp"

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
	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Record r("Ania z zielonego wzgorza", "Montgomery Lucy Maud",
	         "Rudowłosa, piegowata Ania, błąka się po domach dziecka i kolejnych rodzinach zastępczych, by w końcu, przez pomyłkę, trafić na Zielone Wzgórze, pod skrzydła rodzeństwa Cuthbert - Maryli i Mateusza. Z pozoru bardzo zasadniczy nowi opiekunowie, w rzeczywistości są kochani i jedyni na świecie. To u nich Ania Shirley znajduje dom...");

	r.setState(static_cast<Record::State>(2));
	cout << static_cast<short>(r.getState()) << endl;

	Record c(r);
	cout << c.getName() << endl;


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
	while (true) {
		auto c = getKey();
		cout << c.uChar.AsciiChar << " (" << (int) c.uChar.AsciiChar << " / " << c.wVirtualKeyCode << ")" << endl
		     << flush;
	}
#pragma clang diagnostic pop

	return 0;
}