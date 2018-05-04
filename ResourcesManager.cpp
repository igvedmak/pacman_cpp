#include "ResourcesManager.h"
#include "Constants.h"
#include <string>
#include <iostream>
#include <fstream>

using std::ifstream;
using std::string;

ResourcesManager & ResourcesManager::getInstance() {
	static ResourcesManager instance;
	return instance;
}

void ResourcesManager::loadFont(const string& path) {
	_font.loadFromFile(path);
}

sf::Font & ResourcesManager::getFont() {
	return _font;
}

void ResourcesManager::addTexture(const string& path) {
	std::unique_ptr<sf::Texture> t = std::make_unique<sf::Texture>();
	t->loadFromFile(path);
	t->setSmooth(true);

	_textures.insert(std::make_pair(path, std::move(t)));
}

const sf::Texture& ResourcesManager::getTexture(const string& key) {
	auto it = _textures.find(key);
	if (it != _textures.end()) {
		return *((*it).second);
	}
	//TODO Change this
	return sf::Texture();
}


std::vector<std::vector<char>> ResourcesManager::LoadLevel(int level) {
	string file_name = FILE_PREFIX + std::to_string(level) + FILE_POSTFIX;

	ifstream file(file_name);
	string line;
	int size_x;
	int size_y;

	std::vector<std::vector<char>> map;

	//get the size
	getline(file, line);
	sscanf_s(line.c_str(), "%d %d", &size_x, &size_y);

	//Set the frid by size
	map.assign((unsigned int)size_y, std::vector<char>((unsigned int)size_x, ' '));

	//Run on the file and set to the grid
	for (int line_num = 0; line_num < size_y; line_num++)
	{
		getline(file, line);
		for (size_t x = 0; x < line.size(); x++) {
			map[line_num][x] = line[x];
		}
	}

	return map;
}

bool ResourcesManager::isLevelExsits(int level) {
	string file_name = FILE_PREFIX + std::to_string(level) + FILE_POSTFIX;
	ifstream f(file_name);
	bool isGood = f.good();
	f.close();
	return isGood;
}

string ResourcesManager::getBestScore() {
	ifstream f(HIGH_SCORE_FILE);
	string name, line;
	int score;
	f >> name;
	f >> score;
	f.clear();
	f.seekg(0, std::ios::beg);
	getline(f, line);
	_bestScore = score;
	f.close();
	return line;
}
int ResourcesManager::getBestScoreAsNumber()
{
	getBestScore();
	return _bestScore;
}
void ResourcesManager::updateBestScore(int newScore) {
	_bestScore = newScore;
}

void ResourcesManager::updateBestScoreName(string name)
{
	std::ofstream f(HIGH_SCORE_FILE);
	f << name << " " << _bestScore;
	f.close();
}



ResourcesManager::ResourcesManager() {}