#include "MoveComponent.h"
#include "Maths.h"
#include "Actor.h"
#include "Window.h"

MoveComponent::MoveComponent(Actor* ownerP, int updateOrderP):
	Component(ownerP, updateOrderP), forwardSpeed(0.0f), angularSpeed(0.0f)
{
}

void MoveComponent::SetForwardSpeed(float forwardSpeedP)
{
	forwardSpeed = forwardSpeedP;
}

void MoveComponent::SetAngularSpeed(float angularSpeedP)
{
	angularSpeed = angularSpeedP;
}

void MoveComponent::Update(float dt)
{
	if (!Maths::NearZero(angularSpeed)) {
		float newRotation = owner.GetRotation() + angularSpeed * dt;
		owner.SetRotation(newRotation);
	}
	if (!Maths::NearZero(forwardSpeed)) {
		Vector2 newPosition = owner.GetPosition() + owner.GetForward() * forwardSpeed * dt;

		if (newPosition.x < 0) { newPosition.x = windowWidth; }
		else if (newPosition.x > windowWidth) { newPosition.x = 0; }
		if (newPosition.y < 0) { newPosition.y = windowHeigth; }
		else if (newPosition.y > windowHeigth) { newPosition.y = 0; }

		owner.SetPosition(newPosition);
	}
}
