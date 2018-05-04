#pragma once
#include "DrawableObject.h"
#include "EventSubscriber.h"
#include "GameData.h"
#include "Menu.h"
#include "NewRecordBox.h"
#include <memory>
#include <string>

using std::string;

class GameHud : public DrawableObject
{
	public:
		//Constructor that get pos and size
		GameHud(const sf::Vector2f& pos, const sf::Vector2f& size);
		~GameHud();
		//Update the hud
		void update(const GameData& data);
		//Override pure virtual getCenter of DrawableObject
		sf::Vector2f getCenter() const;
		//Override pure virtual draw of DrawableObject
		void draw(sf::RenderWindow& window) const;

	private:
		NewRecordBox _newRecord;
		sf::RectangleShape _rect;
		std::vector<std::unique_ptr<DrawableObject>> _drawables;
		sf::Text _score;
		sf::Text _level;
		sf::Text _life;
		sf::Text _speed;
		std::unique_ptr<Menu> _menu;
		GameData _currentData;
};