#include "Game.h"

bool Game::Initialize() {
	bool isWindowInit = window.Initialize();
	bool isRendererInit = renderer.Initialize(window);
	return isWindowInit && isRendererInit; //Ca retourne des bool jusqu'à trouver une erreur
}

void Game::Loop() {
	while (isRunning) {
		ProcessInput();
		Update();
		Render();
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

	//Escape = Quitter le jeu
	if (keyboardState[SDL_SCANCODE_ESCAPE]) {
		isRunning = false;
	}
}

void Game::Update() {

}

void Game::Render() {
	renderer.BeginDraw();

	renderer.EndDraw();
}


