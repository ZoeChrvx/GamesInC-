#include "BackgroundSpriteComponent.h"
#include "Actor.h"

BackgroundSpriteComponent::BackgroundSpriteComponent(Actor* ownerP, const vector<Texture*>& texturesP, int drawOrderP):
	SpriteComponent(ownerP, *texturesP[0],drawOrderP),
	scrollSpeed(0.0f),
	screenSize(Vector2(windowWidth, windowHeigth))
{
	SetTextures(texturesP);
}

BackgroundSpriteComponent::~BackgroundSpriteComponent()
{
}

void BackgroundSpriteComponent::SetTextures(const vector<Texture*>& texturesP)
{
	int count = 0;
	for (auto tex : texturesP) {
		BGTexture temp{ *tex,Vector2(count * screenSize.x,0) };
		textures.emplace_back(temp);
		count++;
	}
}

void BackgroundSpriteComponent::SetScreenSize(const Vector2& screenSizeP)
{
	screenSize = screenSizeP;
}

void BackgroundSpriteComponent::SetScrollSpeed(float scrollSpeedP)
{
	scrollSpeed = scrollSpeedP;
}

void BackgroundSpriteComponent::Update(float dt)
{
	SpriteComponent::Update(dt);
	for (auto& bg : textures) {
		bg.offset.x += scrollSpeed * dt;
		if (bg.offset.x < -screenSize.x) {
			bg.offset.x = (textures.size() - 1) * screenSize.x - 1;
		}
	}
}

void BackgroundSpriteComponent::Draw(Renderer& renderer)
{
	for (auto& bg : textures) {
		owner.SetPosition(Vector2(bg.offset.x, bg.offset.y));
		renderer.DrawSprite(owner, bg.texture, Rectangle::nullRect, Vector2::zero, Renderer::Flip::None);
	}
}
