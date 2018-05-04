#include "NewRecordBox.h"
#include "ResourcesManager.h"
#include "GameClock.h"
#include "TextInputBox.h"
#include "Constants.h"

NewRecordBox::NewRecordBox(sf::Vector2f winSize):
	_textInput({ 0,0 }, { 0,0 })
{
	
	//The bounding rect
	rect.setSize({ (float)winSize.x / 1.2f, (float)winSize.y / 3.f });
	rect.setPosition(winSize.x/2 , winSize.y/2);
	rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
	rect.setFillColor(sf::Color::White);

	//The border
	rect.setOutlineThickness(2);
	rect.setOutlineColor(sf::Color::Yellow);

	auto boundRect = rect.getGlobalBounds();

	text1.setFont(ResourcesManager::getInstance().getFont());
	text1.setString(NEW_RECORD_TITLE);
	text1.setCharacterSize(25);
	text1.setOrigin(-boundRect.left, -boundRect.top);
	text1.setPosition({ 0,5 });
	text1.setFillColor(sf::Color::Black);
	text1.setOutlineColor(sf::Color::Black);
	text1.setOutlineThickness(0.8f);

	text2.setFont(ResourcesManager::getInstance().getFont());
	text2.setCharacterSize(25);
	text2.setOrigin(-boundRect.left, -boundRect.top);
	text2.setPosition({ 0, 35 });
	text2.setFillColor(sf::Color::Blue);
	text2.setOutlineColor(sf::Color::Black);
	text2.setOutlineThickness(0.8f);

	text3.setFont(ResourcesManager::getInstance().getFont());
	text3.setCharacterSize(25);
	text3.setOrigin(-boundRect.left, -boundRect.top);
	text3.setPosition({ 0,70 });
	text3.setFillColor(sf::Color::Red);
	text3.setOutlineColor(sf::Color::Black);
	text3.setOutlineThickness(0.8f);

	text4.setFont(ResourcesManager::getInstance().getFont());
	text4.setString(NEW_RECORD_ENTER_NAME);
	text4.setCharacterSize(25);
	text4.setOrigin(-boundRect.left, -boundRect.top);
	text4.setPosition({ 0,105 });
	text4.setFillColor(sf::Color::Black);
	text4.setOutlineColor(sf::Color::Black);
	text4.setOutlineThickness(0.8f);

	_textInput.setPos({ rect.getPosition().x - rect.getSize().x/2  , rect.getPosition().y- (rect.getSize().y / 2)+150});
	_textInput.setSize({ rect.getSize().x, rect.getSize().y / 4 });


	text3.setString(LAST_RECORD_TITLE);
	text2.setString(YOUR_RECORD_TITLE);

}


NewRecordBox::~NewRecordBox()
{
}

void NewRecordBox::update(int newRecord)
{
	auto last = ResourcesManager::getInstance().getBestScore();
	text3.setString(LAST_RECORD_TITLE + last);
	text2.setString(YOUR_RECORD_TITLE + std::to_string(newRecord));

	ResourcesManager::getInstance().updateBestScore(newRecord);
}

void NewRecordBox::draw(sf::RenderWindow & window) const
{	
	window.draw(rect);
	window.draw(text1);
	window.draw(text2);
	window.draw(text3);
	window.draw(text4);
	_textInput.draw(window);
}

sf::Vector2f NewRecordBox::getCenter() const
{
	return sf::Vector2f();
}

bool NewRecordBox::isInputClosed()
{		
	return _textInput.isClosed();
}

void NewRecordBox::setMute(bool m)
{
	_textInput.setMute(m);
}
