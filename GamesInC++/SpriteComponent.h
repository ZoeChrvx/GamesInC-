#pragma once
#include "Component.h"
#include "Texture.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(Actor* ownerP, Texture& textureP, int drawOderP = 100);
	virtual ~SpriteComponent();
	SpriteComponent() = delete;
	SpriteComponent(const SpriteComponent&) = delete;
	SpriteComponent& operator=(const SpriteComponent&) = delete;

	virtual void SetTexture(const Texture& textureP);
	virtual void Draw(Renderer& renderer);

	int getDrawOrder() const { return drawOrder; }
	int getTexWidth() const { return texWidth; }
	int getTexHeight() const { return texHeight; }

protected:
	Texture texture;
	int drawOrder;
	int texWidth;
	int texHeight;
};

