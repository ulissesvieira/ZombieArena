#include "pch.h"
#include "TextureHolder.h"
#include <assert.h>

TextureHolder* TextureHolder::m_s_pInstance = nullptr;

TextureHolder::TextureHolder() {
	assert(m_s_pInstance == nullptr);
	m_s_pInstance = this;
}

Texture& TextureHolder::getTexture(string const& filename) {
	// get a reference to m_textures using m_s_pInstance
	auto& m = m_s_pInstance->m_Textures;

	// create an interator to hold a key-value-pair and search for the required kvp
	auto keyValuePair = m.find(filename);
	if (keyValuePair != m.end()) {
		return keyValuePair->second;
	}
	else {
		// filename not found
		// create a new key value pair using the filename
		auto& texture = m[filename];
		// load the texture from file in the usual way
		texture.loadFromFile(filename);

		return texture;
	}
}