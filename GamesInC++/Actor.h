#pragma once
#include <vector>
#include "Vector2.h"
using std::vector;

class Game;
class Component;

class Actor
{
public:
	enum class ActorState {
		Active, Paused, Dead
	};

	Actor();
	virtual ~Actor();
	Actor(const Actor&) = delete;
	Actor& operator=(const Actor&) = delete;

	Game& getGame() const { return game; }
	const ActorState getState() const { return state; }
	const Vector2 getPosition() const { return position; }
	const float getScale()const { return scale; }
	const float getRotation()const { return rotation; }

	void SetPosition(Vector2 positionP);
	void SetScale(float scaleP);
	void SetRotation(float roationP);

	void Update(float dt);
	void UpdateComponents(float dt);
	virtual void UpdateActor(float dt);
	void addComponent(Component* component);
	void removeComponent(Component* component);

private:
	Game& game;
	ActorState state;
	Vector2 position;
	float scale;
	float rotation;

	vector<Component*> components;

};

