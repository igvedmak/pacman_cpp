#pragma once
#include <stack>
#include "PointerPack.h"
#include "State.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class StateManager
{
public:
	StateManager();
	~StateManager();
	void popTop(int amount);
	void leaveBottom(int amount);
	void pushTop(State * state);
	void gameRun();

public:
	void clearStacks();
	sf::Font mFont;
	PointerPack mPack;
	sf::RenderWindow mWindow;
	Sounds mSound;
	std::stack<State *> mClear;
	std::stack<State *> mStates;
};