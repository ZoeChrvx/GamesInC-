#pragma once
#include <string>
#include "Renderer.h"
using std::string;

class Texture
{
public:
	Texture();
	~Texture();

	void Unload();
	bool Load(Renderer& rendererP, const string& filenameP);
	inline SDL_Texture* toSDLTexture() const { return SDLTexture; }
	void UpdateInfo(int& widthOut, int& heigthOut);

	inline int getWidth() const { return width; }
	inline int getHeigth() const { return height; }

private:
	string filename;
	SDL_Texture* SDLTexture;
	int width;
	int height;
};

