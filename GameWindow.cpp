#include "GameWindow.h"
#include "EventsManager.h"
#include "GameClock.h"
#include "ResourcesManager.h"

GameWindow::GameWindow() {
	ResourcesManager::getInstance().addTexture(GAME_TEXTURES);
	ResourcesManager::getInstance().addTexture(BG_TEXTURE);

	_winSize.height = SCREEN_HEIGHT;
	_winSize.width = SCREEN_WIDTH;

	_gameManager = std::make_unique<GameManager>(_winSize);
}


GameWindow::~GameWindow() {}

void GameWindow::start() {
	sf::RenderWindow _window(_winSize, "Pacman by Aviv Cohen & Ori Halamit", sf::Style::Titlebar);
	bool eventPool = false;

	while (_open) {
		eventPool = false;
		sf::Event event;
		while (_window.pollEvent(event) && _open) {
			if (!eventPool)
				eventPool = true;

			_open = _gameManager->update(event);
			eventHandler(event);

			//Set the FPS
			if (GameClock::getInstance().isTimePassed(_lastDrawTime, 1.f / GAME_FPS)) {
				_lastDrawTime = GameClock::getInstance().getElapsedTime();

				_window.clear();
				_gameManager->getGameScreen().draw(_window);
				_gameManager->getGameHud().draw(_window);
				_window.display();
			}
		}

		if (!eventPool) {
			_open = _gameManager->update(event);
		}

		//Set the FPS
		if (GameClock::getInstance().isTimePassed(_lastDrawTime, 1.f / GAME_FPS)) {
			_lastDrawTime = GameClock::getInstance().getElapsedTime();

			_window.clear();
			_gameManager->getGameScreen().draw(_window);
			_gameManager->getGameHud().draw(_window);
			_window.display();
		}
		
	}
}

void GameWindow::eventHandler(sf::Event event) {
	switch (event.type)
	{
		case sf::Event::Closed:
			_open = false;
			break;
		case sf::Event::MouseButtonReleased:
			switch (event.mouseButton.button)
			{
				case sf::Mouse::Right:
					break;
				case sf::Mouse::Left:
					EventsManager::getInstance().fireEvent(ON_MOUSE_UP, event);
					break;
				default:
					break;
			}
			break;
		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
				case sf::Mouse::Right:
					break;
				case sf::Mouse::Left:
					break;
				default:
					break;
			}
			break;

		case sf::Event::MouseMoved:
			EventsManager::getInstance().fireEvent(ON_MOUSE_MOVE, event);
			break;
		case sf::Event::KeyPressed: {
			EventsManager::getInstance().fireEvent(ON_KEY_PRESSED, event);
			break;
		}
		case sf::Event::TextEntered: {
			EventsManager::getInstance().fireEvent(ON_TEXT_ENTERED, event);
			break;
		}
	}
}