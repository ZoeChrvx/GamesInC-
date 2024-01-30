#pragma once

class Timer
{
public:
	Timer();
	Timer(const Timer&) = delete;
	Timer& operator=(const Timer&) = delete;

	//Compute delta time as the number of milliseconds since last frame
	//Clamp it so debug won't think delta time is really high during breakpoints 
	unsigned int ComputeDeltaTime();

	//Attendre si le jeu tourne plus vite que les FPS décidés
	void DelayTime();

private:
	const static unsigned int FPS = 60;
	const static unsigned int frameDelay = 1000 / FPS;
	const unsigned int maxDT = 50;

	//Temps en millisecondes quand la premiere frame commence
	unsigned int frameStart;

	//Temps en millisecondes quand la derniere frame commence
	unsigned int lastFrame;

	//Temps que met la loop a run. Utilisé pour avoir la framerate
	unsigned int frameTime;

};

