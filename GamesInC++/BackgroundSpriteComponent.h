#pragma once
#include "SpriteComponent.h"
#include <vector>
using std::vector;

class BackgroundSpriteComponent : public SpriteComponent
{
public:
	BackgroundSpriteComponent(Actor* ownerP, const vector<Texture*>& texturesP, int drawOrderP = 10);
	virtual ~BackgroundSpriteComponent();
	BackgroundSpriteComponent() = delete;
	BackgroundSpriteComponent(const BackgroundSpriteComponent&) = delete;
	BackgroundSpriteComponent& operator=(const BackgroundSpriteComponent&) = delete;

	float GetScrollSpeed()const { return scrollSpeed; }
	void SetTextures(const vector<Texture*>& textures);
	void SetScreenSize(const Vector2& screenSizeP);
	void SetScrollSpeed(float scrollSpeedP);
	
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

private:
	struct BGTexture {
		BGTexture(Texture& t, Vector2 o) :texture(t), offset(o) {}
		Texture& texture;
		Vector2 offset;
	};

	std::vector<BGTexture>textures;
	Vector2 screenSize;
	float scrollSpeed;
};

