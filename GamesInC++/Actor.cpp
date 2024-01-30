#include "Actor.h"
#include <algorithm>
#include "Game.h"
#include "Component.h"

Actor::Actor() :
	state(ActorState::Active),
	position(Vector2::zero),
	scale(1.0f),
	rotation(0.0f),
	game(Game::instance()) {
	game.AddActor(this);
}

Actor::~Actor() {
	game.RemoveActor(this);
	while (!components.empty()) {
		delete components.back();
	}
}

void Actor::SetPosition(Vector2 positionP) {
	position = positionP;
}

void Actor::SetScale(float scaleP) {
	scale = scaleP;
}

void Actor::SetRotation(float rotationP) {
	rotation = rotationP;
}

void Actor::Update(float dt) {
	if (state == Actor::ActorState::Active) {
		UpdateComponents(dt);
		UpdateActor(dt);
	}
}

void Actor::UpdateComponents(float dt) {
	for (auto component : components) {
		component->Update(dt);
	}
}

void Actor::UpdateActor(float dt) {

}

void Actor::addComponent(Component* component) {
	int myOrder = component->getUpdateOrder();
	auto iter = begin(components);
	for (; iter != end(components); ++iter) {
		if (myOrder < (*iter)->getUpdateOrder()) {
			break;
		}
	}
	components.insert(iter, component);

}

void Actor::removeComponent(Component* component){
	auto iter = std::find(begin(components), end(components), component);
	if (iter != end(components)) {
		components.erase(iter);
	}
}


