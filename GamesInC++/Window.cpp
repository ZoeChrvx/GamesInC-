#include "Window.h"
#include "Log.h"

Window::Window() :SDLWindow(nullptr), width(windowWidth), heigth(windowHeigth) 
{
}

bool Window::Initialize()
{
	int sdlInitResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlInitResult != 0) {
		Log::error(LogCategory::Video, "Unable to initialize SDL");
		return false;
	}
	SDLWindow = SDL_CreateWindow("Wall Pong", 100, 000, width, heigth, 0); //0 is flag, we will use later

	if (!SDLWindow) {
		Log::error(LogCategory::Systeme, "Failed to create a Window");
		return false;
	}
	return true;
}

void Window::Close() {
	SDL_DestroyWindow(SDLWindow);
}
