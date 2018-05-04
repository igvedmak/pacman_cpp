#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameScreen.h"
#include "GameHud.h"
#include "GameManager.h"

class GameWindow
{
	public:
		//Constructor
		GameWindow();
		~GameWindow();
		//Start the game
		void start();

	private:
		sf::VideoMode _winSize;
		std::unique_ptr<GameManager> _gameManager;
		bool _open = true;
		float _lastDrawTime = 0;
		//Handle the events
		void eventHandler(sf::Event event);
};

