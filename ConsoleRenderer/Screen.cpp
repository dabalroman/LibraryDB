#include "Screen.hpp"

void Screen::addRenderable(Renderable *r) {
	renderables.push_back(r);
}

vector<Renderable *> *Screen::getRenderables() {
	return &renderables;
}

Screen::Screen(Console &consoleHandle_, DataKeeper &dataHandle_) {
	consoleHandle = &consoleHandle_;
	dataHandle = &dataHandle_;

}
