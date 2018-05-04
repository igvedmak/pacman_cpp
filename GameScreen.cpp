#include "GameScreen.h"
#include "Wall.h"
#include "Cookie.h"
#include "ResourcesManager.h"
#include "Constants.h"
#include "EnemyAI.h"
#include "GameClock.h"
#include "GameObjectFactory.h"

using namespace std::placeholders;

using std::vector;

GameScreen::GameScreen(const sf::Vector2f& pos, const sf::Vector2f& size)
	: _maxSize(size) {
	_rect.setPosition(pos);
	_rect.setFillColor(sf::Color::Black);
}

GameScreen::~GameScreen() {}

bool GameScreen::loadLevel(int level) {
	//Checks if level exists
	if (ResourcesManager::getInstance().isLevelExsits(level)) {
		_lastAIUpdateTime = 0;
		_cookiesCount = 0;

		//Load the level
		_map = ResourcesManager::getInstance().LoadLevel(level);
		_gridSize = { (int)_map[0].size(), (int)_map.size() };

		//Set rect size
		if (_gridSize.x > _gridSize.y) {
			_rect.setSize({ _maxSize.x, (_maxSize.x / _gridSize.x) *_gridSize.y });
		} else {
			_rect.setSize({ (_maxSize.y / _gridSize.y) *_gridSize.x, _maxSize.y });
		}

		//Sets enemyAI rect Game Rect
		EnemyAI::getInstance().setGameRect(_rect.getGlobalBounds());

		_elfs.clear();
		_grid.clear();
		//Init the grid
		for (int y = 0; y < _gridSize.y; y++) {
			_grid.push_back(std::vector<std::unique_ptr<GameObject>>());
			for (int x = 0; x < _gridSize.x; x++) {
				_grid[y].push_back(std::unique_ptr<GameObject>());
			}
		}
		
		//Set each grid cell object by char
		for (int y = 0; y < _map.size(); y++) {
			for (int x = 0; x < _map[y].size(); x++) {
				addByChar(_map[y][x], { x, y });
			}
		}

		EventSubscriber::muteEvents(false);
		return true;
	}
	return false;
}

void GameScreen::addByChar(char c,  const sf::Vector2i& gridPos) {
	//Calculate the object size by map size
	int max = std::max(_gridSize.x, _gridSize.y);
	float max_size = std::max(_rect.getSize().x, _rect.getSize().y);
	sf::Vector2f objectSize = sf::Vector2f(max_size / max, max_size / max);

	auto pos = _rect.getPosition();

	//Get the object creator
	GameObjectBaseCreator * creator = GameObjectFactory::getInstance().getCreator(c);
	if (creator != NULL) {
		auto canMoveLambda = [&](Moveable & obejct, Direction direction) { return canMove(obejct, direction); };
		GameObject * go = creator->create(sf::Vector2f(pos.x + gridPos.x * objectSize.x, pos.y + gridPos.y * objectSize.y), objectSize);
		//Checks which object to create
		if (typeid(*go) == typeid(Pacman)) {
			_pacman.reset(static_cast<Pacman *>(go));
			_pacman->canMove(canMoveLambda);
		} else if (typeid(*go) == typeid(Elf)) {
			_elfs.push_back(std::unique_ptr<Elf>(static_cast<Elf *>(go)));
			_elfs.back()->canMove(canMoveLambda);
		} else {
			_grid[gridPos.y][gridPos.x] = std::unique_ptr<GameObject>(go);
			if (typeid(*go) == typeid(Cookie))
				_cookiesCount++;
		}
	}
}

int GameScreen::getCookiesCount() {
	return _cookiesCount;
}

void GameScreen::removeGameObjectFromGrid(const sf::Vector2i& pos){
	if (_grid[pos.y][pos.x]->getTextureType() == CookieTexture) {
		_cookiesCount--;
	}
	_grid[pos.y][pos.x] = nullptr;

}

int GameScreen::getElfsCount() {
	return (int)_elfs.size();
}

sf::Vector2f GameScreen::getCenter() const {
	//TODO
	return sf::Vector2<float>();
}

void GameScreen::draw(sf::RenderWindow & window) const {
	static sf::Clock c;
	static bool firstTime = true;

	window.draw(_rect);
	
	for (int y = 0; y < _grid.size(); y++) {
		for (int x = 0; x < _grid[y].size(); x++) {
			if (_grid[y][x])
				_grid[y][x]->draw(window);
		}
	}
		
	if (_pacman)
		_pacman->draw(window);

	for (int i = 0; i < _elfs.size(); i++) {
		_elfs[i]->draw(window);
	}

	c.restart();
	
}

std::pair<sf::Vector2i, GameObject&> GameScreen::getInteraction() {
	GameObject * enemy;
	if (_pacman) {
		auto rect = _pacman->getBoundingRect();
		auto myrect = _rect.getGlobalBounds();
		auto center = _pacman->getCenter();

		auto pacmanPos = getPacmanGrisPos();

		//Checks intersection between pacman and cooike
		if (gridIntersectsExists(*_pacman, 0, 0, CookieTexture)) {
			return { pacmanPos, *_grid[pacmanPos.y][pacmanPos.x] };
		}

		//Checks intersection between pacman and enemy
		if ((enemy = checkEnemyIntersects()) != nullptr) {
			return { pacmanPos, *enemy };
		}
	}
	
	return  { {-1,-1}, *_pacman };
}

Pacman& GameScreen::getPacman() {
	return *_pacman;
}

void GameScreen::resetLevel() {
	if(_pacman)
		_pacman->resetToStartPosition();

	for (int i = 0; i < _elfs.size(); i++) {
		_elfs[i]->resetToStartPosition();
	}
}

bool GameScreen::keyPressed(const sf::Event& event) {
	if (_pacman) {
		//Change the pacman direction by key
		switch (event.key.code) {
			case sf::Keyboard::Up:
				_pacman->moveDirection(Up);
				break;
			case sf::Keyboard::Down:
				_pacman->moveDirection(Down);
				break;
			case sf::Keyboard::Left:
				_pacman->moveDirection(Left);
				break;
			case sf::Keyboard::Right:
				_pacman->moveDirection(Right);
				break;
		}
	}

	return false;
}

bool GameScreen::textEntered(const sf::Event & event)
{
	return false;
}

bool GameScreen::canMove(Moveable & obejct, Direction direction) {
	auto myrect = _rect.getGlobalBounds();

	Figure& go = dynamic_cast<Figure&>(obejct);

	auto rect = go.getBoundingRect();

	//Checks if can move by direction
	switch (direction) {
		case Up:
			rect.top -= 1;
			if (gridIntersectsExists(go, 0, -1, WallTexture))
				return false;
			return std::round(rect.top) >= myrect.top;
		case Down:
			rect.top += 1;
			if (gridIntersectsExists(go, 0, 1, WallTexture))
				return false;
			return std::round(rect.top + rect.height) <= myrect.top + myrect.height;
		case Left:
			rect.left -= 1;
			if (gridIntersectsExists(go, -1, 0, WallTexture))
				return false;
			return std::round(rect.left) >= myrect.left;
		case Right:
			rect.left += 1;
			if (gridIntersectsExists(go, 1, 0, WallTexture))
				return false;
			return std::round(rect.left + rect.width) <= myrect.left + myrect.width;

	}

	return false;
}

bool GameScreen::gridIntersectsExists(Figure& go, int offset_x, int offset_y, TextureType type) {
	auto gameObjectRect = go.getBoundingRect();

	sf::Vector2i gameObjectCell = {
		(int)((go.getCenter().x - _rect.getGlobalBounds().left) / (gameObjectRect.width)),
		(int)((go.getCenter().y - _rect.getGlobalBounds().top) / (gameObjectRect.height))
	};

	//Fix values if out of grid
	gameObjectCell.x = gameObjectCell.x >= _gridSize.x ? _gridSize.x - 1 : (gameObjectCell.x < 0) ? 0 : gameObjectCell.x;
	gameObjectCell.y = gameObjectCell.y >= _gridSize.y ? _gridSize.y - 1 : (gameObjectCell.y < 0) ? 0 : gameObjectCell.y;

	//Claculate the grid cell center position of GameObject by x and y
	sf::Vector2f gridCellOfGameObjectCenter = {
		gameObjectRect.width * gameObjectCell.x + (gameObjectRect.width / 2) + _rect.getPosition().x,
		gameObjectRect.height * gameObjectCell.y + (gameObjectRect.height / 2) + _rect.getPosition().y
	};

	//Calculate the new x, y after complete move
	sf::Vector2i newGameObjectCell = {
		gameObjectCell.x + offset_x,
		gameObjectCell.y + offset_y
	};

	//Set the rect to move to new position
	gameObjectRect.left += offset_x;
	gameObjectRect.top += offset_y;

	//Checks if new grid x and y of GameObject are in range
	if (newGameObjectCell.x >= 0 && newGameObjectCell.x < _gridSize.x &&
		newGameObjectCell.y >= 0 && newGameObjectCell.y < _gridSize.y) {
		//Fix the pos if very close to center of cell
		go.fixPosition(gridCellOfGameObjectCenter);
		if (_grid[newGameObjectCell.y][newGameObjectCell.x] != nullptr &&
			_grid[newGameObjectCell.y][newGameObjectCell.x]->getTextureType() == type &&
			_grid[newGameObjectCell.y][newGameObjectCell.x]->intersects(gameObjectRect)) {
			//If intersects
			return true;
		} else if (offset_y != 0 && !(std::abs(gridCellOfGameObjectCenter.x - go.getCenter().x) < 1.0f)) {
			//If move Up or Down and x is not centered
			return true;
		} else if (offset_x != 0 && !(std::abs(gridCellOfGameObjectCenter.y - go.getCenter().y) < 1.0f)) {
			//If move Left or Right and y is not centered
			return true;
		}
	}



	return false;
}


GameObject * GameScreen::checkEnemyIntersects()
{
	if (_pacman) {
		for (int i = 0; i < _elfs.size(); i++)
		{
			auto enemy = _elfs[i]->getBoundingRect();
			//Avoid when the vertices of the rect are intersects
			enemy.top += 1;
			enemy.left += 1;
			enemy.width -= 1;
			enemy.height -= 1;
			if (_pacman->intersects(enemy))
				return  _elfs[i].get();
		}
	}
	return nullptr;
}

void GameScreen::updateAI() {
	static std::vector<std::vector<AStarNode>> BFS;
	
	if (!_pacman || _map.size() == 0 || _elfs.size() == 0)
		return;

	//Update the BFS every UDATE_BFS_SEC sec
	if(GameClock::getInstance().isTimePassed(_lastAIUpdateTime, UPDATE_BFS_SEC)) {
		_lastAIUpdateTime = GameClock::getInstance().getElapsedTime();

		EnemyAI::getInstance().update(getPacmanGrisPos(), { _gridSize.x, _gridSize.y }, _grid);
	}
}


void GameScreen::muteEvents(bool mute) {
	EventSubscriber::muteEvents(mute);
	
	if (_pacman)
		_pacman->muteEvents(mute);

	for (int i = 0; i < _elfs.size(); i++) {
		_elfs[i]->muteEvents(mute);
	}
}

sf::Vector2i GameScreen::getPacmanGrisPos() {
	//Calculate pacman pos in grid
	int pacman_x = (int)std::round((_pacman->getBoundingRect().left - _rect.getGlobalBounds().left) / ((float)_pacman->getBoundingRect().width));
	int pacman_y = (int)std::round((_pacman->getBoundingRect().top - _rect.getGlobalBounds().top) / ((float)_pacman->getBoundingRect().height));
	pacman_x = pacman_x >= _gridSize.x ? _gridSize.x - 1 : (pacman_x < 0) ? 0 : pacman_x;
	pacman_y = pacman_y >= _gridSize.y ? _gridSize.y - 1 : (pacman_y < 0) ? 0 : pacman_y;
	return { pacman_x ,pacman_y };
}
