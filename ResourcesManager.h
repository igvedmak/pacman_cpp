#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <unordered_map>

using std::string;
using std::unordered_map;

typedef unordered_map<string, std::unique_ptr<sf::Texture>> TexturesMap;

class ResourcesManager
{
	public:
		//Singleton get instance
		static ResourcesManager& getInstance();
		//Load the font of the game
		void loadFont(const string& path);
		//Get the font of the game
		sf::Font& getFont();
		//Add texture to map
		void addTexture(const string& path);
		//Get texture from map
		const sf::Texture& getTexture(const string& key);
		//Checks if level exists
		bool isLevelExsits(int level);
		//Load the level
		std::vector<std::vector<char>> LoadLevel(int level);
		//Get from file the last best score
		string getBestScore();
		//Get it as a number
		int getBestScoreAsNumber();
		//Update the new best score
		void updateBestScore(int newScore);
		//Update its name in the file
		void updateBestScoreName(string name);
	private:
		int _bestScore;
		sf::Font _font;
		TexturesMap _textures;
		ResourcesManager();
};

