//
// Created by rd on 20.05.2019.
//

#include "ConsoleRenderer.hpp"

void ConsoleRenderer::insertStringIntoBuffer(ConsoleRenderer::RICHTEXT &buffer, string s, COORD coord,
                                             Console::COLOR color) {
	for (int i = coord.Y; i < buffer.size(); i++) {
		for (int j = coord.X; j < buffer[i].size() && (j - coord.X) < s.length(); j++) {
			buffer[i][j] = {s[j - coord.X], color};
		}
	}
}
