#pragma once
#include "Window.h"
#include "Renderer.h"
#include "Vector2.h"
#include "Actor.h"
using std::vector;

class Game
{
public:
	static Game& instance() {
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator =(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game() :
		isRunning(true),
		isUpdatingActors(false)
	{}

public:
	bool Initialize();
	void Loop();
	void Close();

	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

private:
	void ProcessInput();
	void Update(float dt);
	void Render();

	bool isRunning;
	Renderer renderer;
	Window window;

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;
};