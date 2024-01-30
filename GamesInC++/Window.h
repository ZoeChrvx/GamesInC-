#pragma once
#include <SDL.h>

const int windowHeigth = 800;
const int windowWidth = 768;

class Window
{
public:
	Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	bool Initialize();
	void Close();

	SDL_Window* getSDLWindow()const { return SDLWindow; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }

private:
	SDL_Window* SDLWindow;
	int width;
	int height;
};

