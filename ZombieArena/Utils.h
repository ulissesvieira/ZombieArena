#pragma once

#include <SFML/Graphics.hpp>
#include "WorldConstants.h"
#include "Zombie.h"

using namespace sf;

int createBackground(VertexArray& rVA, IntRect arena);
std::shared_ptr<Zombie> createHorde(int numZombie, IntRect arena);