#pragma once
#include "MoveComponent.h"
#include <SDL_stdinc.h>

class InputComponent:public MoveComponent
{
public:
	InputComponent(Actor* ownerP);
	InputComponent() = delete;
	InputComponent(const InputComponent&) = delete;
	InputComponent& operator=(const InputComponent&) = delete;

	void ProcessInput(const Uint8* keyState);

	void SetMaxForwardSpeed(float maxForwardSpeedP);
	void SetMaxAngularSpeed(float maxAngularSpeedP);
	void SetForwardKey(int key);
	void SetBackKey(int key);
	void SetClockwiseKey(int key);
	void SetCounterClockwiseKey(int key);

private:
	float maxForwardSpeed;
	float maxAngularSpeed;

	int forwardKey;
	int backKey;
	int clockwiseKey;
	int counterClockwiseKey;
};

