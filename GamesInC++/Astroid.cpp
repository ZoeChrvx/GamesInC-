#include "Astroid.h"
#include "Random.h"
#include "Window.h"
#include "Maths.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Assets.h"

Astroid::Astroid() :Actor() {
	Vector2 randPos = Random::GetVector(Vector2::zero, Vector2(windowWidth, windowHeigth));
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.0f, Maths::twoPi));

	SpriteComponent* sc = new SpriteComponent(this, Assets::GetTexture("Astroid"));
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);
}
