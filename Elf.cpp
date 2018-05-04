#include "Elf.h"
#include "EnemyAI.h"
#include "GameClock.h"

Elf::Elf(TextureColor color, const sf::Vector2f& pos, const sf::Vector2f& size)
	: Figure(ElfTexture, color, pos, size) {
	_isSmart = rand() % 2;
	_defaultSpeed = DEFAULT_ELF_SPEED;
}

Elf::~Elf() {}

void Elf::move() {
	if (_isSmart) {
		//Move by the AI
		moveDirection(EnemyAI::getInstance().getDirection(this));
	} else {
		//Move by current direction every UPDATE_STUPID_ELF_SEC sec
		if(GameClock::getInstance().isTimePassed(_lastDirectionChange, UPDATE_STUPID_ELF_SEC)) {
			_lastDirectionChange = GameClock::getInstance().getElapsedTime();
			switch (getMovingDirection())
			{
				case Up:
				case Down:
					moveDirection((rand() % 2) ? Left : Right);
					break;
				case Left:
				case Right:
					moveDirection((rand() % 2) ? Up : Down);
					break;
				case None: {
					for (int i = 0; i < 4;  i++) {
						if (_canMoveFunc(*this, (Direction)i)) {
							moveDirection((Direction)(i));
							break;
						}
					}
					break;
				}
			}
		}
	}

	Figure::move();
}

