#include "pch.h"
#include "World.h"

World::World()
{
	// start with game over state
	state = State::GAME_OVER;

	// get the screen resolution and create an SFML window
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	window.create(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Fullscreen);

	// create an SFML Viwq for the main action
	mainView.reset(FloatRect(0, 0, (float) resolution.x, (float) resolution.y));

	// the main game loop
	while (window.isOpen()) {
		handleInput();
	}
}

World::~World()
{
}

void World::handleInput() {
	Event event;

	while (window.pollEvent(event)) {
		if (event.type == Event::KeyPressed) {
			// pause a game while playing 
			if (event.key.code == Keyboard::Return && state == State::PLAYING) {
				state = State::PAUSED;
			}
			// restart while paused
			else if (event.key.code == Keyboard::Return && state == State::PAUSED) {
				state = State::PLAYING;
				// reset the clock so there isn't a frame jump
				clock.restart();
			}
			// start a new game while in GAME_OVER state
			else if (event.key.code == Keyboard::Return && state == State::GAME_OVER) {
				state = State::LEVELING_UP;
			}

			if (state == State::PLAYING)
			{
			}
		}
	}

	
}