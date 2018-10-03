#include "pch.h"
#include "CreateBackground.h"

int createBackground(VertexArray & rVA, IntRect arena)
{
	// anything we do to rVA we are actually doing to background (in the main function)
	// how big is each tile/texture
	int worldWidth = arena.width / WorldConstants::TILE_SIZE;
	int worldHeight = arena.height / WorldConstants::TILE_SIZE;

	// what type of primitive are we using?
	rVA.setPrimitiveType(Quads);

	// set the size of the vertex array
	rVA.resize(worldWidth * worldHeight * WorldConstants::VERTS_IN_QUAD);

	// start at the beginning of the vertex array
	int currentVertex = 0;

	for (int w = 0; w < worldWidth; w++) {
		for (int h = 0; h < worldHeight; h++) {
			// position each vertex in the current quad
			rVA[currentVertex + 0].position = Vector2f(w * WorldConstants::TILE_SIZE, h * WorldConstants::TILE_SIZE);
			rVA[currentVertex + 1].position = Vector2f((w * WorldConstants::TILE_SIZE) + WorldConstants::TILE_SIZE, h * WorldConstants::TILE_SIZE);
			rVA[currentVertex + 2].position = Vector2f((w * WorldConstants::TILE_SIZE) + WorldConstants::TILE_SIZE, (h * WorldConstants::TILE_SIZE) + WorldConstants::TILE_SIZE);
			rVA[currentVertex + 3].position = Vector2f(w * WorldConstants::TILE_SIZE, (h * WorldConstants::TILE_SIZE) + WorldConstants::TILE_SIZE);

			// define the position in the texture for current quad
			// either grass, stone, bush or wall
			if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1) {
				rVA[currentVertex + 3].texCoords = Vector2f(0, WorldConstants::TILE_SIZE + WorldConstants::TILE_TYPES * WorldConstants::TILE_SIZE);

				// use the wall texture
				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + WorldConstants::TILE_TYPES * WorldConstants::TILE_SIZE);
				rVA[currentVertex + 1].texCoords = Vector2f(WorldConstants::TILE_SIZE, 0 + WorldConstants::TILE_TYPES * WorldConstants::TILE_SIZE);
				rVA[currentVertex + 2].texCoords = Vector2f(WorldConstants::TILE_SIZE, WorldConstants::TILE_SIZE + WorldConstants::TILE_TYPES * WorldConstants::TILE_SIZE);
				rVA[currentVertex + 3].texCoords = Vector2f(0, WorldConstants::TILE_SIZE + WorldConstants::TILE_TYPES * WorldConstants::TILE_SIZE);
			} 
			else {
				// Use a random floor texture
				srand((int)time(0) + h * w - h);
				int mOrG = (rand() % WorldConstants::TILE_TYPES);
				int verticalOffset = mOrG * WorldConstants::TILE_SIZE;

				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
				rVA[currentVertex + 1].texCoords = Vector2f(WorldConstants::TILE_SIZE, 0 + verticalOffset);
				rVA[currentVertex + 2].texCoords = Vector2f(WorldConstants::TILE_SIZE, WorldConstants::TILE_SIZE + verticalOffset);
				rVA[currentVertex + 3].texCoords = Vector2f(0, WorldConstants::TILE_SIZE + verticalOffset);
			}
			
			// position ready for the next for vertices
			currentVertex = currentVertex + WorldConstants::VERTS_IN_QUAD;
		}
	}

	return WorldConstants::TILE_SIZE;
}
