#include "pch.h"
#include "World.h"
#include "Utils.h"

World::World()
{
	// start with game over state
	state = State::PLAYING;

	// hide the mouse pointer and replace it with crosshair
	window.setMouseCursorVisible(false);
	textureCrosshair = TextureHolder::getTexture("graphics/crosshair.png");
	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 25);

	// get the screen resolution and create an SFML window
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	window.create(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Fullscreen);

	// create an SFML Viwq for the main action
	mainView.reset(FloatRect(0, 0, (float) resolution.x, (float) resolution.y));

	textureBackground = TextureHolder::getTexture("graphics/background_sheet.png");

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
				case Keyboard::R:
					if (bulletsSpare >= clipSize) {
						// plenty of bullets. Reload.
						bulletsInClip = clipSize;
						bulletsSpare -= clipSize;
					}
					else if (bulletsSpare > 0) {
						// only a few bullets left
						bulletsInClip = bulletsSpare;
						bulletsSpare = 0;
					}
					else {
						// more here soon?!
					}
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

		if (Mouse::isButtonPressed(Mouse::Left)) {
			if ((gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 1000 / fireRate) && bulletsInClip > 0) {
				currentBullet++;
				if (currentBullet >= WorldConstants::NUMBER_BULLETS) {
					// pass the center of the player and the center of the crosshair to the shoot function
					bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.y);
					currentBullet = 0;
					lastPressed = gameTimeTotal;
					bulletsInClip--;
				}
			}
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
		}  // leveling up	
	}	

	// handle the player quitting
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
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
		//int titleSize = 50;
		// pass the vertex array by reference to the background function
		int tileSize = createBackground(background, arena);

		// spawn the player int the middle of the arena
		player.spawn(arena, resolution, tileSize);

		// create a harde of zombies
		numZombies = WorldConstants::NUMBER_ZOMBIES;
		zombies.reset();
		zombies = createHorde(numZombies, arena);
		numZombiesAlive = numZombies;

		// reset the clock so there isn't a frame jump
		clock.restart();
	}
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
		// make a note of the players new position
		Vector2f playerPosition(player.getCenter().x, player.getCenter().y);
		// make the view centre around the player
		mainView.setCenter(playerPosition);

		// set the crosshair to the mouse world location
		spriteCrosshair.setPosition(mouseWorldPosition);

		// loop through each zombie and update them
		for (int i = 0; i < numZombies; i++) {
			if (zombies.get()[i].isAlive()) {				
				zombies.get()[i].update(dt.asSeconds(), playerPosition);
			}
		}

		// update any bullets that are in-flight
		for (int i = 0; i < WorldConstants::NUMBER_BULLETS; i++) {
			if (bullets[i].isInFlight()) {
				bullets[i].update(dtAsSeconds);
			}
		}
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

		// draw the background
		window.draw(background, &textureBackground);

		// loop through each zombie and update them
		for (int i = 0; i < numZombies; i++) {
			window.draw(zombies.get()[i].getSprite());
		}

		for (int i = 0; i < WorldConstants::NUMBER_BULLETS; i++) {
			if (bullets[i].isInFlight()) {				
				window.draw(bullets[i].getShape());
			}
		}

		// draw the player
		window.draw(player.getSprite());

		// draw the crosshair
		window.draw(spriteCrosshair);

		window.display();
		break;
	default:
		break;
	}	
}