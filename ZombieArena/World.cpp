#include "pch.h"
#include "World.h"

World::World()
{
	// start with game over state
	state = State::GAME_OVER;

	// get the screen resolution and create an SFML window
	resolution.x = 800; // VideoMode::getDesktopMode().width;
	resolution.y = 600; // VideoMode::getDesktopMode().height;

	window.create(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Default);

	// create an SFML Viwq for the main action
	mainView.reset(FloatRect(0, 0, (float) resolution.x, (float) resolution.y));

	// the main game loop
	while (window.isOpen()) {
		handleInput();
		update();
		draw();
	}
}

World::~World()
{
}

void World::handleInput() {
	sf::Event event;

	while (window.pollEvent(event)) {
		D(std::cerr << event.type << " EP: " << sf::Event::KeyPressed << " ER: " << sf::Event::KeyReleased << std::endl;)

		if (event.type == sf::Event::Closed) {
			window.close();
		}

		if (event.type == sf::Event::KeyPressed) {
			D(std::cerr << "key pressed " << event.key.code << std::endl;)
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

			if (state == State::PLAYING) {
				switch (event.key.code)
				{
				case Keyboard::W:
					player.moveDirection(Direction::UP);
					break;
				case Keyboard::A:
					player.moveDirection(Direction::LEFT);
					break;
				case Keyboard::S:
					player.moveDirection(Direction::DOWN);
					break;
				case Keyboard::D:
					player.moveDirection(Direction::RIGHT);
					break;
				default:
					player.moveDirection(Direction::STAND_BY);
					break;
				}
			}
		} 
		else if (event.type == sf::Event::KeyReleased) {
			D(std::cerr << "key released " << event.key.code << std::endl;)
			if (state == State::PLAYING) {
				switch (event.key.code)
				{
				case Keyboard::W:										
				case Keyboard::A:					
				case Keyboard::S:					
				case Keyboard::D:
					player.moveDirection(Direction::STAND_BY);
					break;
				default:					
					break;
				}
			}
		}
	}

	// handle the player quitting
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	if (state == State::PLAYING) {
		// handle the player LEVING UP
		switch (event.key.code)
		{
		case Keyboard::Num1:
		case Keyboard::Num2:
		case Keyboard::Num3:
		case Keyboard::Num4:
		case Keyboard::Num5:
		case Keyboard::Num6:
			state = State::PLAYING;
			break;
		default:
			break;
		}

		// if the state is STILL playing
		if (state == State::PLAYING) {
			// prepare the level
			// we will modify the next two lines later 
			arena.width = 500;
			arena.height = 500;
			arena.left = 0;
			arena.top = 0;

			// we will modify this line of code later
			int titleSize = 50;
			// spawn the player int the middle of the arena
			player.spawn(arena, resolution, titleSize);
			// reset the clock so there isn't a frame jump
			clock.restart();
		}
	} // leveling up
}

void World::update() {
	if (state == State::PLAYING) {
		// update the delta time
		Time dt = clock.restart();
		// update the total game time
		gameTimeTotal += dt;
		// make a decimal fraction of 1 from the delta time
		float dtAsSeconds = dt.asSeconds();
		// where is the mouse pointer
		mouseScreenPosition = Mouse::getPosition();
		// convert mouse position to world coordinates of main view
		mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);

		// update the player
		player.update(dtAsSeconds, mouseScreenPosition);
		// make the view centre around the player
		mainView.setCenter((float) player.getCenter().x, (float) player.getCenter().y);

		// make a note of the players new position
		Vector2i playerPosition(player.getCenter());
	}
}

void World::draw() {
	switch (state)
	{
	case State::PAUSED:
		break;
	case State::LEVELING_UP:
		break;
	case State::GAME_OVER:
		break;
	case State::PLAYING: 
		window.clear();

		// set the main view to be displayed in the window
		// and draw everything related to it
		window.setView(mainView);

		// draw the player
		window.draw(player.getSprite());

		window.display();
		break;
	default:
		break;
	}	
}