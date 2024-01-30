#include "Game.h"
#include "Timer.h"
#include "Assets.h"

bool Game::Initialize() {
	bool isWindowInit = window.Initialize();
	bool isRendererInit = renderer.Initialize(window);

	int windowWidth = window.getWidth();
	int windowHeight = window.getHeight();

	return isWindowInit && isRendererInit; //Ca retourne des bool jusqu'à trouver une erreur
}

void Game::Load() {
	Assets::loadTexture(renderer, "Res/Ship01.png", "ship01");
}

void Game::Unload() {
	while (!actors.empty()) {
		delete actors.back();
	}

	Assets::Clear();
}

void Game::Loop() {
	Timer timer;
	float dt = 0;
	while (isRunning) {
		float dt = timer.ComputeDeltaTime() / 1000.0f;
		ProcessInput();
		Update(dt);
		Render();
		timer.DelayTime();
	}
}

void Game::Close() {
	renderer.Close();
	window.Close();
	SDL_Quit();
}

void Game::ProcessInput() {
	//SDL Event
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}

	//Assignation des touches
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
}

void Game::Update(float dt) {
	isUpdatingActors = true;
	for (auto actor : actors) {
		actor->Update(dt);
	}
	isUpdatingActors = false;

	for (auto pendingActor : pendingActors) {
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	vector<Actor*> deadActors;
	for (auto actor : actors) {
		if (actor->getState() == Actor::ActorState::Dead) {
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors) {
		delete deadActor;
	}
}

void Game::Render() {
	renderer.BeginDraw();

	renderer.EndDraw();
}

void Game::AddActor(Actor* actor) {
	if (isUpdatingActors) {
		pendingActors.emplace_back(actor);
	}
	else {
		actors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor) {
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors)) {
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors)) {
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}


