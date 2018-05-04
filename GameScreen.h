#pragma once
#include <memory>
#include "DrawableObject.h"
#include "Typeable.h"
#include "Pacman.h"
#include "Elf.h"
#include <thread>

class GameScreen : public DrawableObject, public Typeable
{
	public:
		//Constructor that get pos and size
		GameScreen(const sf::Vector2f& pos, const sf::Vector2f& size);
		~GameScreen();

		//Load lecel if exsits
		bool loadLevel(int level);
		//Return the cookies count
		int getCookiesCount();
		//Remove gameobhect form grid
		void removeGameObjectFromGrid(const sf::Vector2i& pos);
		//Returns the elfs count
		int getElfsCount();
		//Override pure virtual getCenter of DrawableObject
		sf::Vector2f getCenter() const;
		//Override pure virtual draw of DrawableObject
		void draw(sf::RenderWindow& window) const;
		//Return interaction if exsits
		std::pair<sf::Vector2i, GameObject &> getInteraction();
		//Return the pacman
		Pacman& getPacman();
		//reset the level
		void resetLevel();
		//Update the ai
		void updateAI();
		//Mute the event of the screen
		void muteEvents(bool mute);
		//Get the pacman pos in grid
		sf::Vector2i getPacmanGrisPos();


	private:
		sf::Vector2i _gridSize;
		sf::RectangleShape _rect;
		std::unique_ptr<Pacman> _pacman;
		sf::Vector2f _maxSize;
		std::vector<std::unique_ptr<Elf>> _elfs;
		std::vector<std::vector<std::unique_ptr<GameObject>>> _grid;
		std::vector<std::vector<char>> _map;
		float _lastAIUpdateTime = 0;

		int _cookiesCount = 0;

		//Override pure virtual keyPressed of Typeable
		bool keyPressed(const sf::Event& event);
		//Override pure virtual textEntered of Typeable
		bool textEntered(const sf::Event& event);

		//Call back of can move for objects
		bool canMove(Moveable& obejct, Direction direction);
		//Return if there is grid intersects with type
		bool  gridIntersectsExists(Figure& go, int offset_x, int offset_y, TextureType type);
		//Add game object by char
		void addByChar(char c, const sf::Vector2i& gridPos);
		//Return gameobject if exsits
		GameObject * checkEnemyIntersects();

};

