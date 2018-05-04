#include "TextInputBox.h"
#include "ResourcesManager.h"
#include "EventsManager.h"
#include "Constants.h"

TextInputBox::TextInputBox(sf::Vector2<float> size, sf::Vector2<float> pos) :
	_font(ResourcesManager::getInstance().getFont()),
	_size(size), _pos(pos),
	_boxClosed(false) {
	setPadding(10, 10, 10, 10);
}

void TextInputBox::setPadding(float top, float bottom, float left, float right)
{
	_paddingTL = { left, top };
	_paddingBR = { right, bottom };
}

TextInputBox::~TextInputBox()
{
}

void TextInputBox::draw(sf::RenderWindow & window) const
{
	float inner_height = (_size.y - (_paddingTL.y + _paddingBR.y));
	float inner_width = (_size.x - (_paddingTL.x + _paddingBR.x));

	//The bounding rect
	sf::RectangleShape rect(_size);
	rect.setPosition(_pos);
	rect.setFillColor(sf::Color::Black);


	//The border
	rect.setOutlineThickness(2);
	rect.setOutlineColor(sf::Color::Blue);

	//Set new render textrue to avoid overflow of text
	sf::RenderTexture renderTexture;
	renderTexture.create((int)inner_width, (int)inner_height);
	renderTexture.clear(sf::Color::Transparent);

	//Set the text to draw
	sf::Text m_text;
	m_text.setCharacterSize((int)inner_height);
	m_text.setFont(_font);
	m_text.setString(_text);
	m_text.setFillColor(sf::Color::White);
	m_text.setOrigin(m_text.getLocalBounds().left, m_text.getLocalBounds().top);

	//Set text pos by align

	m_text.setPosition(0, (inner_height - m_text.getLocalBounds().height) / 2.0f);

	//m_text.setPosition((inner_width - m_text.getLocalBounds().width) / 2.0f,
	//(inner_height - m_text.getLocalBounds().height) / 2.0f);

	//Draw the text on the render texture
	renderTexture.draw(m_text);
	renderTexture.display();

	//Convert the render texture to sprite
	sf::Sprite sprite(renderTexture.getTexture());
	sprite.setPosition(_pos.x + _paddingTL.x, _pos.y + _paddingTL.y);

	//Draw the bounding rect and the sprite on the window
	window.draw(rect);
	window.draw(sprite);
}



sf::Vector2f TextInputBox::getCenter() const
{
	return sf::Vector2f();
}

//When enter is pressed close the box
bool TextInputBox::keyPressed(const sf::Event & event)
{
	if (_mute) {
		return true;
	}

	if (event.key.code == sf::Keyboard::Return)
	{
		ResourcesManager::getInstance().updateBestScoreName(_text);
		_boxClosed = true;
		_mute = true;
		_text = "";
		EventsManager::getInstance().fireEvent(ON_NEW_RECORD_END, event);
		return true;
	}




	return false;
}

bool TextInputBox::textEntered(const sf::Event & event)
{
	if (event.text.unicode < 128) {
		unsigned short unicode = event.text.unicode;
		if (unicode == 8) {
			removeLastChar();
		}
		else {
			addChar((char)event.text.unicode);
		}
		return true;
	}
	return false;
}

void TextInputBox::setPos(sf::Vector2f pos)
{
	_pos = pos;
}

void TextInputBox::setSize(sf::Vector2f size)
{
	_size = size;
}

string TextInputBox::getName()
{
	return _nameEnterd;
}

bool TextInputBox::isClosed()
{
	if (_boxClosed) {
		_boxClosed = false;
		return true;
	}
	return _boxClosed;
}

void TextInputBox::setMute(bool m)
{
	_mute = m;
}

void TextInputBox::addChar(char c)
{
	if (_text.size() < MAX_NAME) {
		_text += c;
	}
}

void TextInputBox::removeLastChar()
{
	if (!_text.empty())
		_text.pop_back();
}