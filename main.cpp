#ifdef _DEBUG
#pragma comment ( lib , "sfml-main-d.lib" )
#elif defined (NDEBUG)
#pragma comment ( lib , "sfml-main.lib" )
#else
#error "Unrecognized configuration!"
#endif

#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "GameWindow.h"
#include "GameObjectFactory.h"


int main() {
	GameWindow game;
	game.start();

	return EXIT_SUCCESS;
}