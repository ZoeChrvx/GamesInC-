#include "Game.h"
#include "Timer.h"

bool Game::Initialize() {
	bool isWindowInit = window.Initialize();
	bool isRendererInit = renderer.Initialize(window);

	int windowWidth = window.getWidth();
	int windowHeigth = window.getHeigth();
	topWall = { 0,0,static_cast<float>(windowWidth), wallThickness };
	bottomWall = { 0, windowHeigth - wallThickness, static_cast<float>(windowWidth), wallThickness };
	midWall = { (float)windowWidth / 2,0,wallThickness,static_cast<float>(windowHeigth) };

	return isWindowInit && isRendererInit; //Ca retourne des bool jusqu'à trouver une erreur
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

	//Escape = Quitter le jeu
	if (keyboardState[SDL_SCANCODE_ESCAPE]) {
		isRunning = false;
	}

	//Paddle left move
	if (keyboardState[SDL_SCANCODE_W]) {
		paddleLeftDirection = -1;
	}
	if(keyboardState[SDL_SCANCODE_S]) {
		paddleLeftDirection = 1;
	}

	//Paddle right move
	if (keyboardState[SDL_SCANCODE_UP]) {
		paddleRightDirection = -1;
	}
	if (keyboardState[SDL_SCANCODE_DOWN]) {
		paddleRightDirection = 1;
	}
}

void Game::Update(float dt) {
	//Paddle left move
	paddleLeftPos += paddleLeftVelocity * dt * paddleLeftDirection;
	if (paddleLeftPos.y < paddleHeigth / 2 + wallThickness) {
		paddleLeftPos.y = paddleHeigth / 2 + wallThickness;
	}
	if (paddleLeftPos.y > window.getHeigth() - paddleHeigth / 2 - wallThickness) {
		paddleLeftPos.y = window.getHeigth() - paddleHeigth / 2 - wallThickness;
	}

	//Paddle right move
	paddleRightPos += paddleRightVelocity * dt * paddleRightDirection;
	if (paddleRightPos.y < paddleHeigth / 2 + wallThickness) {
		paddleRightPos.y = paddleHeigth / 2 + wallThickness;
	}
	if (paddleRightPos.y > window.getHeigth() - paddleHeigth / 2 - wallThickness) {
		paddleRightPos.y = window.getHeigth() - paddleHeigth / 2 - wallThickness;
	}

	//Ball move
	ballPos += ballVelocity * dt;
	if (ballPos.y < ballSize / 2 + wallThickness) {
		ballPos.y = ballSize / 2 + wallThickness;
		ballVelocity.y *= -1;
	}
	else if (ballPos.y > window.getHeigth() - ballSize / 2 - wallThickness) {
		ballPos.y = window.getHeigth() - ballSize / 2 - wallThickness;
		ballVelocity.y *= -1;
	}
	/*if (ballPos.x > window.getWidth() - ballSize / 2 - wallThickness) {
		ballPos.x = window.getWidth() - ballSize / 2 - wallThickness;
		ballVelocity.x *= -1;
	}*/

	//Ball-Paddle collision
	Vector2 diffLeft = ballPos - paddleLeftPos;
	if (fabsf(diffLeft.y) <= paddleHeigth / 2
		&& fabsf(diffLeft.x) <= paddleWidth / 2 + ballSize / 2
		&& ballVelocity.x < 0) {
		ballVelocity.x *= -1;
		ballPos.x = paddleLeftPos.x + paddleWidth / 2 + ballSize / 2;
	}
	Vector2 diffRight = ballPos - paddleRightPos;
	if (fabsf(diffRight.y) <= paddleHeigth / 2
		&& fabsf(diffRight.x) <= paddleWidth / 2 + ballSize / 2
		&& ballVelocity.x < 0) {
		ballVelocity.x *= -1;
		ballPos.x = paddleRightPos.x + paddleWidth / 2 + ballSize / 2;
	}

	//Restart automatically
	if (ballPos.x < 0) {
		ballVelocity.x *= -1;
		ballPos.x = window.getWidth() / 2.f;
		ballPos.y = window.getHeigth() / 2.f;
	}
	else if (ballPos.x > window.getWidth() - ballSize / 2) {
		ballVelocity.x *= -1;
		ballPos.x = window.getWidth() / 2.f;
		ballPos.y = window.getHeigth() / 2.f;
	}
}

void Game::Render() {
	renderer.BeginDraw();

	renderer.DrawRectOpacityLow(midWall);
	renderer.DrawRect(topWall);
	renderer.DrawRect(bottomWall);

	Rectangle ballRect = { ballPos.x - ballSize / 2,ballPos.y - ballSize / 2,ballSize,ballSize };
	renderer.DrawRect(ballRect);

	Rectangle paddleLeftRect = { paddleLeftPos.x - paddleWidth / 2, paddleLeftPos.y - paddleHeigth / 2, paddleWidth,paddleHeigth };
	renderer.DrawRect(paddleLeftRect);

	Rectangle paddleRightRect = { paddleRightPos.x - paddleWidth / 2, paddleRightPos.y - paddleHeigth / 2, paddleWidth, paddleHeigth };
	renderer.DrawRect(paddleRightRect);

	renderer.EndDraw();
}


