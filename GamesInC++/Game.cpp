#include "Game.h"

bool Game::Initialize() {
	bool isWindowInit = window.Initialize();
	bool isRendererInit = renderer.Initialize(window);

	int windowWidth = window.getWidth();
	int windowHeigth = window.getHeigth();
	topWall = { 0,0,static_cast<float>(windowWidth), wallThickness };
	bottomWall = { 0, windowHeigth - wallThickness, static_cast<float>(windowWidth), wallThickness };
	rightWall = { windowWidth - wallThickness,0,wallThickness,static_cast<float>(windowHeigth) };

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

	renderer.DrawRect(topWall);
	renderer.DrawRect(bottomWall);
	renderer.DrawRect(rightWall);

	Rectangle ballRect = { ballPos.x - ballSize / 2,ballPos.y - ballSize / 2,ballSize,ballSize };
	renderer.DrawRect(ballRect);

	Rectangle paddleRect = { paddlePos.x - paddleWidth / 2,paddlePos.y - paddleHeigth / 2, paddleWidth,paddleHeigth };
	renderer.DrawRect(paddleRect);

	renderer.EndDraw();
}


