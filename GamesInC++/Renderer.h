#pragma once
#include "Rectangle.h"
#include <SDL.h>
#include "Window.h"

class Renderer
{
public:
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	bool Initialize(Window& window);
	void BeginDraw();
	void DrawRect(Rectangle& rect);
	void DrawRectOpacityLow(Rectangle& rect);
	void EndDraw();
	void Close();

private:
	SDL_Renderer* SDLRenderer = nullptr;
};

