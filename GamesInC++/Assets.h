#pragma once
#include <map>
#include <string>
#include "Texture.h"
using std::map;
using std::string;

class Assets
{
public:
	static std::map<std::string, Texture> textures;

	static Texture loadTexture(Renderer& renderer, const string& filename, const string& name);

	static Texture& GetTexture(const std::string& name);

	static void Clear();

private:
	Assets() {}

	static Texture loadTextureFromFile(Renderer& renderer, const string& filename);
};

