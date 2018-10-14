#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class TextureHolder {
private:
	// a map container from the stl that holds related pairs of string and texture
	map<string, Texture> m_Textures;

	// a pointer of the same type as the class itself
	// the one and only instance
	static TextureHolder *m_s_pInstance;
public:
	TextureHolder();
	static Texture& getTexture(string const& filename);
};