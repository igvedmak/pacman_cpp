#include "EnemyAI.h"
#include <SFML/Graphics.hpp>
#include <queue>
#include "Wall.h"

EnemyAI & EnemyAI::getInstance() {
	static EnemyAI instance;
	return instance;
}

void EnemyAI::update(const sf::Vector2i& pacmanPos, const sf::Vector2i& enemyPos, const std::vector<std::vector<std::unique_ptr<GameObject>>>& map)
{
	BFS.clear();
	BFS.assign(map.size(), std::vector<AStarNode>(map[0].size()));

	std::vector<sf::Vector2i> path;
	std::priority_queue<PriorityNode> frontier;
	frontier.push({ pacmanPos, 0 });
	BFS[pacmanPos.y][pacmanPos.x].came_from = pacmanPos;
	BFS[pacmanPos.y][pacmanPos.x].cost_so_far = 0;
	BFS[pacmanPos.y][pacmanPos.x].is_used = true;
	while (!frontier.empty()) {
		sf::Vector2i current = frontier.top().value;
		frontier.pop();

		//Comment To act as Greedy BFS With out early exit
		/*if (current == enemyPos) {
			break;
		}*/

		std::vector<sf::Vector2i> neighbors = getNeighbors(map, current);

		for (size_t i = 0; i < neighbors.size(); i++) {
			sf::Vector2i next = neighbors[i];
			int new_cost = BFS[current.y][current.x].cost_so_far + 1;

			if (!BFS[next.y][next.x].is_used || new_cost < BFS[next.y][next.x].cost_so_far) {
				double priority = new_cost + heuristic(enemyPos, next);
				BFS[next.y][next.x].is_used = true;
				BFS[next.y][next.x].cost_so_far = new_cost;
				BFS[next.y][next.x].came_from = current;
				frontier.push({ next, priority });
			}

		}
	}
}

Direction EnemyAI::getDirection(GameObject * go) {
	//Checks if there is BFS grid
	if (!BFS.empty()) {
		//Return the nect pos by current pos
		int elf_x = (int)std::round((go->getBoundingRect().left - _gameRect.left) / (go->getBoundingRect().width));
		int elf_y = (int)std::round((go->getBoundingRect().top - _gameRect.top) / (go->getBoundingRect().height));

		elf_x = elf_x >= (int)BFS[0].size() ? (int)BFS[0].size() - 1 : (elf_x < 0) ? 0 : elf_x;
		elf_y = elf_y >= (int)BFS.size() ? (int)BFS.size() - 1 : (elf_y < 0) ? 0 : elf_y;

		sf::Vector2i current = BFS[elf_y][elf_x].came_from;

		if (current.x == elf_x + 1) {
			return Right;
		}
		else if (current.x == elf_x - 1) {
			return Left;
		}
		else if (current.y == elf_y + 1) {
			return Down;
		}
		else if (current.y == elf_y - 1) {
			return Up;
		}
	}
	return None;
}


void EnemyAI::setGameRect(sf::FloatRect& gameRect) {
	_gameRect = gameRect;
}

double EnemyAI::heuristic(const sf::Vector2i& a, const sf::Vector2i& b) {
	return abs(a.x - b.x) + abs(a.y - b.y);;
}

std::vector<sf::Vector2i> EnemyAI::getNeighbors(const std::vector<std::vector<std::unique_ptr<GameObject>>>& map, const sf::Vector2i& current) {
	std::vector<sf::Vector2i> neighbors;
	sf::Vector2i v[4];

	v[0] = { current.x + 1, current.y };
	v[1] = { current.x, current.y - 1 };
	v[2] = { current.x, current.y + 1 };
	v[3] = { current.x - 1, current.y };

	for (size_t i = 0; i < 4; i++) {
		if (v[i].y >= 0 && v[i].y < map.size() &&
			v[i].x >= 0 && v[i].x < map[0].size()) {
			if(map[v[i].y][v[i].x]== nullptr ||
					(map[v[i].y][v[i].x] &&
					 typeid(*map[v[i].y][v[i].x]) != typeid(Wall)))
				neighbors.push_back(v[i]);
		}
	}

	return neighbors;
}

EnemyAI::EnemyAI() {}