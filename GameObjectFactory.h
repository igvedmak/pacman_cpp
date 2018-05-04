#pragma once
#include <string>
#include <unordered_map>
#include "Constants.h"
#include "GameObject.h"
#include "Pacman.h"
#include "Wall.h"
#include "Cookie.h"
#include "Elf.h"

using std::unordered_map;
using std::string;

class GameObjectBaseCreator {
	public:
		//Create the object
		virtual GameObject * create(const sf::Vector2f& pos, const sf::Vector2f& size) = 0;
};

template <class T>
class GameObjectCreator : public GameObjectBaseCreator {
	public:
		//Constructor
		GameObjectCreator() {}
		//Constructor that get color
		GameObjectCreator(TextureColor color) {
			m_color = color;
		}
		//Create the object (Pure virtual)
		GameObject * create(const sf::Vector2f& pos, const sf::Vector2f& size) {
			return new T(m_color, pos, size);
		}
	private:
		TextureColor m_color = Red;
};

class GameObjectFactory {
	public:
		//Singleton get instance
		static GameObjectFactory& getInstance() {
			static GameObjectFactory instance;
			return instance;
		}

		~GameObjectFactory() {}

		//Get the creator by char
		GameObjectBaseCreator * getCreator(char name) {
			auto it = _objects.find(name);
			if (it != _objects.end()) {
				return (*it).second.get();
			}
			return NULL;
		}

	private:
		GameObjectFactory() {
			//Set the objects that the creator can create
			_objects.insert(std::make_pair('@', new GameObjectCreator<Pacman>(Red)));
			_objects.insert(std::make_pair('W', new GameObjectCreator<Pacman>(Green)));
			_objects.insert(std::make_pair('S', new GameObjectCreator<Pacman>(Blue)));
			_objects.insert(std::make_pair('#', new GameObjectCreator<Wall>(Red)));
			_objects.insert(std::make_pair('E', new GameObjectCreator<Wall>(Green)));
			_objects.insert(std::make_pair('D', new GameObjectCreator<Wall>(Blue)));
			_objects.insert(std::make_pair('*', new GameObjectCreator<Cookie>(Red)));
			_objects.insert(std::make_pair('I', new GameObjectCreator<Cookie>(Green)));
			_objects.insert(std::make_pair('K', new GameObjectCreator<Cookie>(Blue)));
			_objects.insert(std::make_pair('%', new GameObjectCreator<Elf>(Red)));
			_objects.insert(std::make_pair('T', new GameObjectCreator<Elf>(Green)));
			_objects.insert(std::make_pair('G', new GameObjectCreator<Elf>(Blue)));
		}

		unordered_map<char, std::unique_ptr<GameObjectBaseCreator>> _objects;
};

