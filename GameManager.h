#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameScreen.h"
#include "GameHud.h"
#include "GameData.h"
#include "Typeable.h"
#include <SFML/Audio.hpp>

class GameManager : public Typeable
{
	public:
		//Constructor that get the window size
		GameManager(sf::VideoMode _winSize);
		~GameManager();
		//Update the game
		bool update(sf::Event event);
		//Returns the GameScreen
		GameScreen& getGameScreen();
		//Reutrns GameHud
		GameHud& getGameHud();
		//Override pure virtual onFire EventSubscriber
		bool onFire(const string& eventName, const sf::Event& event);
		//Check for new record
		void newRecord(int score);


	protected:
		//Override the keyPressed of Typeable
		bool keyPressed(const sf::Event& event);
		//Override pure virtual textEntered of Typeable
		bool textEntered(const sf::Event& event);
	private:
		GameData _data;
		sf::Vector2i _gridSize;
		std::unique_ptr<GameScreen> _screen;
		std::unique_ptr<GameHud> _hud;
		//Set the sounds of the game
		void SetSounds();
		//When Game over 
		void gameOver();
		//Handle the interactions 
		void handleInteractions();
		//Handle pacman collision with cookie
		void pacmanCookie(GameObject& pacman,  GameObject & cookie);
		//Handle pacman collision with elf
		void pacmanElf(GameObject& pacman, GameObject & elf);

};

