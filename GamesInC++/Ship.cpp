#include "Ship.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "InputComponent.h"
#include "Maths.h"

Ship::Ship() : Actor()
{
	SpriteComponent* sc = new SpriteComponent(this, Assets::GetTexture("Ship"));
	InputComponent* ic = new InputComponent(this);
	ic->SetForwardSpeed(300.0f);
	ic->SetMaxAngularSpeed(Maths::twoPi);
}
