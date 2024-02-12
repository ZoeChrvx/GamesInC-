#pragma once
#include <vector>
#include "SpriteComponent.h"
using std::vector;

class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(Actor* ownerP, const vector<Texture*>& textureP, int drawOrderP = 100);
	virtual ~AnimSpriteComponent();
	AnimSpriteComponent() = delete;
	AnimSpriteComponent(const AnimSpriteComponent&) = delete;
	AnimSpriteComponent& operator=(const AnimSpriteComponent&) = delete;

	float getAnimFPS()const { return animFPS; }
	void SetAnimTextures(const vector<Texture*>& texturesP);
	void SetAnimFPS(float animFSPS);

	void Update(float dt) override;

private:
	vector<Texture*> animTextures;
	float currentFrame;
	float animFPS;
};

