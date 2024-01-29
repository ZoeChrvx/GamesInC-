#include "Renderer.h"
#include "Log.h"

Renderer::Renderer() :SDLRenderer(nullptr) {

}

bool Renderer::Initialize(Window& window) {
	SDLRenderer = SDL_CreateRenderer(window.getSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!SDLRenderer) {
		Log::error(LogCategory::Video, "Failed to create renderer");
		return false;
	}
	return true;
}

void Renderer::BeginDraw() {
	SDL_SetRenderDrawColor(SDLRenderer, 120, 120, 255, 255);
	SDL_RenderClear(SDLRenderer);
}

void Renderer::EndDraw() {
	SDL_RenderPresent(SDLRenderer);
}

void Renderer::DrawRect(Rectangle& rect) {
	SDL_SetRenderDrawColor(SDLRenderer, 255, 255, 255, 255);
	SDL_Rect SDLRect = rect.toSDLRect();
	SDL_RenderFillRect(SDLRenderer, &SDLRect);
}

void Renderer::Close() {
	SDL_DestroyRenderer(SDLRenderer);
}