#include <SDL.h>

int main(int argc, char** argv)
{
	//Taille de l'�cran
	const int screenWidth = 800;	//SCREEN_WIDTH
	const int screenHeigth = 450;	//SCREEN_HEIGTH

	//Window Pointer
	SDL_Window* window = nullptr;

	//Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	//Cr�ation d'une fenetre
	window = SDL_CreateWindow("First Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeigth, SDL_WINDOW_SHOWN);

	//Delai de 2 secondes
	SDL_Delay(2000);

	//D�truire la fenetre
	SDL_DestroyWindow(window);

	//Quitter SDL
	SDL_Quit();

	return 0;
}