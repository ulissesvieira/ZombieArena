#include "pch.h"
#include "Utils.h"

std::shared_ptr<Zombie> createHorde(int numZombies, IntRect arena) {	
	std::shared_ptr<Zombie> zombies(new Zombie[numZombies], std::default_delete<Zombie[]>());	

	int maxY = arena.height - 20;
	int minY = arena.top + 20;
	int maxX = arena.width - 20;
	int minX = arena.left + 20;

	for (int i = 0; i < numZombies; i++) {
		// which side should the zombie spwan
		srand((int)time(0) * i);
		int side = (rand() % 4);
		float x, y;

		switch (side)
		{
		case 0: // left
			x = minX;
			y = (rand() % maxY) + minY;
			break;
		case 1: // right
			x = maxX;
			y = (rand() % maxY) + minY;
			break;
		case 2: // top
			x = (rand() % maxX) + minX;
			y = minY;
			break;
		case 3: // bottom
			x = (rand() % maxX) + minX;
			y = maxY;
			break;		
		}

		// bloater, crawler or runner
		srand((int)time(0) * i * 2);
		int type = (rand() % 3);
		switch (type)
		{
		case 0:
			zombies.get()[i].spawn(x, y, WorldConstants::ZombieType::BLOATER, i);
			break;
		case 1:
			zombies.get()[i].spawn(x, y, WorldConstants::ZombieType::CRAWLER, i);
			break;
		default:
			zombies.get()[i].spawn(x, y, WorldConstants::ZombieType::CHASER, i);
			break;
		}
	}

	return zombies;
}