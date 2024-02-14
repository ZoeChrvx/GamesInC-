#include "InputComponent.h"
#include <SDL_scancode.h>

InputComponent::InputComponent(Actor* ownerP):
	MoveComponent(ownerP),
	maxForwardSpeed(100.0f),
	maxAngularSpeed(1.0f),
	forwardKey(SDL_SCANCODE_W),
	backKey(SDL_SCANCODE_S),
	clockwiseKey(SDL_SCANCODE_S),
	counterClockwiseKey(SDL_SCANCODE_A)
{
}

void InputComponent::ProcessInput(const Uint8* keyState)
{
	float forwardSpeed = 0.0f;
	if (keyState[forwardKey]) {
		forwardSpeed += maxForwardSpeed;
	}
	if (keyState[backKey]) {
		forwardSpeed -= maxForwardSpeed;
	}
	SetForwardSpeed(forwardSpeed);

	float angularSpeed = 0.0f;
	if (keyState[clockwiseKey]) {
		angularSpeed += maxAngularSpeed;
	}
	if (keyState[counterClockwiseKey]) {
		angularSpeed -= maxAngularSpeed;
	}
	SetAngularSpeed(angularSpeed);
}

void InputComponent::SetMaxForwardSpeed(float maxForwardSpeedP)
{
	maxForwardSpeed = maxForwardSpeedP;
}

void InputComponent::SetMaxAngularSpeed(float maxAngularSpeedP)
{
	maxAngularSpeed = maxAngularSpeedP;
}

void InputComponent::SetForwardKey(int key)
{
	forwardKey = key;
}

void InputComponent::SetBackKey(int key)
{
	backKey = key;
}

void InputComponent::SetClockwiseKey(int key)
{
	clockwiseKey = key;
}

void InputComponent::SetCounterClockwiseKey(int key)
{
	counterClockwiseKey = key;
}
