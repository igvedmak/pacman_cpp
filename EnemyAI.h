#pragma once
#include "Constants.h"
#include "GameObject.h"

#include <SFML/Graphics.hpp>
#include <memory>

struct AStarNode {
	sf::Vector2i came_from;
	int cost_so_far = 0;
	bool is_used = false;
};

struct PriorityNode {
	sf::Vector2i value;
	double priority;

	bool operator<(const PriorityNode& other) const {
		return priority > other.priority;
	}
};

class EnemyAI
{
	public:
		//Singleton get instance
		static EnemyAI& getInstance();
		//Update the bfs
		void update(const sf::Vector2i& pacmanPos, const sf::Vector2i& enemyPos, const std::vector<std::vector<std::unique_ptr<GameObject>>>& map);
		//Return the direction to move for the game object
		Direction getDirection(GameObject * go);
		//Set the game rect for the calculation
		void setGameRect(sf::FloatRect& gameRect);
	private:
		//Calculate the manhaten distance
		double heuristic(const sf::Vector2i& a, const sf::Vector2i& b);
		//Return the neighbors of cell
		std::vector<sf::Vector2i> getNeighbors(const std::vector<std::vector<std::unique_ptr<GameObject>>>& map, const sf::Vector2i& current);

		std::vector<std::vector<AStarNode>> BFS;
		sf::FloatRect _gameRect;
		EnemyAI();
};

