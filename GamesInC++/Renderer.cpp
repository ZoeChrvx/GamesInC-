#include "Renderer.h"
#include "Log.h"
#include "Texture.h"
#include "Maths.h"
#include "SpriteComponent.h"
#include <SDL_image.h>

Renderer::Renderer() :SDLRenderer(nullptr) {

}



bool Renderer::Initialize(Window& window) {
	SDLRenderer = SDL_CreateRenderer(window.getSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!SDLRenderer) {
		Log::error(LogCategory::Video, "Failed to create renderer");
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		Log::error(LogCategory::Video, "Failed to create renderer");
		return false;
	}
	return true;
}

void Renderer::BeginDraw() {
	SDL_SetRenderDrawColor(SDLRenderer, 120, 120, 255, 255);
	SDL_RenderClear(SDLRenderer);
}

void Renderer::Draw() {
	DrawSprites();
}

void Renderer::EndDraw() {
	SDL_RenderPresent(SDLRenderer);
}

void Renderer::DrawRect(Rectangle& rect) {
	SDL_SetRenderDrawColor(SDLRenderer, 255, 255, 255, 255);
	SDL_Rect SDLRect = rect.toSDLRect();
	SDL_RenderFillRect(SDLRenderer, &SDLRect);
}

void Renderer::DrawSprites() {
	for (auto sprite : sprites) {
		sprite->Draw(*this);
	}
}

void Renderer::DrawSprite(const Actor& actor, const Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const {
	SDL_Rect dstRect;
	Vector2 position = actor.GetPosition();
	float rotation = actor.GetRotation();
	float scale = actor.GetScale();

	dstRect.w = static_cast<int>(tex.getWidth() * scale);
	dstRect.h = static_cast<int>(tex.getHeigth() * scale);

	dstRect.x = static_cast<int>(position.x - origin.x);
	dstRect.y = static_cast<int>(position.y - origin.y);

	SDL_Rect* srcSDL = nullptr;
	if (srcRect != Rectangle::nullRect)
	{
		srcSDL = new SDL_Rect
		{
			Maths::round(srcRect.x),
			Maths::round(srcRect.y),
			Maths::round(srcRect.width),
			Maths::round(srcRect.height)
		};
	}

	SDL_RenderCopyEx(
		SDLRenderer,
		tex.toSDLTexture(),
		srcSDL,
		&dstRect,
		-Maths::toDegrees(rotation),
		nullptr,
		SDL_FLIP_NONE);

	delete srcSDL;
}

void Renderer::AddSprite(SpriteComponent* sprite) {
	int spriteDrawOrder = sprite->getDrawOrder();
	auto iter = begin(sprites);
	for (; iter != end(sprites); ++iter) {
		if (spriteDrawOrder < (*iter)->getDrawOrder()) break;
	}
	sprites.insert(iter, sprite);
}

void Renderer::RemoveSprite(SpriteComponent* sprite) {
	auto iter = std::find(begin(sprites), end(sprites), sprite);
	sprites.erase(iter);
}


void Renderer::Close() {
	SDL_DestroyRenderer(SDLRenderer);
}