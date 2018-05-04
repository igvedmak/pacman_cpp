#include "Menu.h"
#include "EventsManager.h"
#include "Constants.h"
#include "ResourcesManager.h"

using namespace std::placeholders;

Menu::Menu(const sf::Vector2f& size)
	: _rect(size) {
	float heightJumps = size.y / 5;

	_buttons.push_back(std::make_unique<RectButton>(
		sf::Vector2f(size.x / 2, heightJumps * 1), 
		sf::Vector2f(200.f, 50.f), sf::Color::White, 
		sf::Color::Red, ResourcesManager::getInstance().getFont(), 
		MENU_RESUME, ON_GAME_RESUME));
	_buttons.push_back(std::make_unique<RectButton>(
		sf::Vector2f(size.x / 2, heightJumps * 2), 
		sf::Vector2f(200.f, 50.f), sf::Color::White, 
		sf::Color::Red, ResourcesManager::getInstance().getFont(), 
		MENU_NEW_GAME, ON_GAME_START));
	_buttons.push_back(std::make_unique<RectButton>(
		sf::Vector2f(size.x / 2, heightJumps * 3), 
		sf::Vector2f(400.f, 50.f), sf::Color::White, 
		sf::Color::Red, ResourcesManager::getInstance().getFont(), 
		MENU_TOGGLE_SOUND, ON_SOUND_STATE_CHANGED));
	_buttons.push_back(std::make_unique<RectButton>(
		sf::Vector2f(size.x / 2, heightJumps * 4), 
		sf::Vector2f(200.f, 50.f), sf::Color::White, 
		sf::Color::Red, ResourcesManager::getInstance().getFont(), 
		MENU_EXIT, ON_GAME_EXIT));

	for (int i = 0; i < _buttons.size(); i++) {
		_buttons[i]->onMouseUp(
			[&](const string& eventName, const sf::Event& event, EventSubscriber& obejct) { 
				return menuSelect(eventName, event, obejct); 
			}
		);
	}
	
	_rect.setPosition(0, 0);
	_rect.setTexture(&ResourcesManager::getInstance().getTexture(BG_TEXTURE));
}

Menu::~Menu() {}

sf::Vector2f Menu::getCenter() const {
	return sf::Vector2<float>();
}

void Menu::draw(sf::RenderWindow & window) const {
	if (_show) {
		window.draw(_rect);
		int counter = 0;
		for (int i = 0; i < _buttons.size(); i++) {
			if(_buttons[i]->getText() != MENU_RESUME || _isPaused)
				_buttons[i]->draw(window);
		}
	}
}

bool Menu::menuSelect(const string& eventName, const sf::Event& event, EventSubscriber& obejct) {
	RectButton& button = dynamic_cast<RectButton&>(obejct);

	if (button.getEventName().size() > 0) {
		EventsManager::getInstance().fireEvent(button.getEventName(), sf::Event());
		return true;
	}
	return false;
}

void Menu::showMenu(bool show, bool isPaused) {
	//Show menu and listen to events by show 
	_show = show;
	_isPaused = isPaused;
	mute(!show);
}

void Menu::mute(bool isMute) {
	for (int i = 0; i < _buttons.size(); i++) {
		_buttons[i]->muteEvents(isMute);
	}
}
