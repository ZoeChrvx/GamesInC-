#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"
#include "Timer.h"
#include "Assets.h"
#include "BackgroundSpriteComponent.h"
#include "Astroid.h"
#include "Ship.h"

bool Game::Initialize() {
	bool isWindowInit = window.Initialize();
	bool isRendererInit = renderer.Initialize(window);

	int windowWidth = window.getWidth();
	int windowHeight = window.getHeight();

	return isWindowInit && isRendererInit; //Ca retourne des bool jusqu'à trouver une erreur
}

void Game::Load() {
	//Textures
	Assets::LoadTexture(renderer, "Res/Ship.png", "Ship");
	/*Assets::LoadTexture(renderer, "Res/Ship01.png", "Ship01");
	Assets::LoadTexture(renderer, "Res/Ship02.png", "Ship02");
	Assets::LoadTexture(renderer, "Res/Ship03.png", "Ship03");
	Assets::LoadTexture(renderer, "Res/Ship04.png", "Ship04");*/
	Assets::LoadTexture(renderer, "Res/Farback01.png", "Farback01");
	Assets::LoadTexture(renderer, "Res/Farback02", "Farback02");
	Assets::LoadTexture(renderer, "Res/Stars.png", "Stars");
	Assets::LoadTexture(renderer, "Res/Astroid.png", "Astroid");

	/*
	auto actor = new Actor();
	auto sprite = new SpriteComponent(actor, Assets::getTexture("Ship01"));
	actor->SetPosition(Vector2{ 100,100 });
	

	//Sprite Animé
	vector<Texture*> animTextures{
		&Assets::GetTexture("Ship01"),
		&Assets::GetTexture("Ship02"),
		&Assets::GetTexture("Ship03"),
		&Assets::GetTexture("Ship04")
	};*/

	//Ship
	Ship* ship = new Ship();
	ship->SetPosition(Vector2{ 100,300 });

	//Background
	//"Far" BG
	vector<Texture*> bgTextsFar{
		&Assets::GetTexture("Farback01"),
		&Assets::GetTexture("Farback02")
	};
	Actor* bgFar = new Actor();
	BackgroundSpriteComponent* bgSpritesFar = new BackgroundSpriteComponent(bgFar, bgTextsFar);
	bgSpritesFar->SetScrollSpeed(-100.0f);

	//"Close" BG
	Actor* bgClose = new Actor();
	std::vector<Texture*> bgTextsClose{
		&Assets::GetTexture("Stars"),
		&Assets::GetTexture("Stars")
	};
	BackgroundSpriteComponent* bgSpritesClose = new BackgroundSpriteComponent(bgClose, bgTextsClose);
	bgSpritesClose->SetScrollSpeed(-200.0f);

	const int astroidNumber = 20;
	for (int i = 0; i < astroidNumber; ++i) {
		new Astroid();
	}
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
	
	//Actor Input
	isUpdatingActors = true;
	for (auto actor : actors) {
		actor->ProcessInput(keyboardState);
	}
	isUpdatingActors = false;
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
		if (actor->GetState() == Actor::ActorState::Dead) {
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors) {
		delete deadActor;
	}
}

void Game::Render() {
	renderer.BeginDraw();
	renderer.Draw();
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


