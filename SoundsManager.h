#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include <memory>
#include <unordered_map>

using std::unordered_map;
using std::string;


struct BufferAndSound {
	sf::SoundBuffer _buffer;
	sf::Sound _sound;
};

typedef unordered_map<string, std::unique_ptr<BufferAndSound>> SoundsMap;

class SoundsManager
{
	public:
		//Singleton getInstance
		static SoundsManager& getInstance();
		//Add the sound by path
		void addSound(const string& path, int volume = 100);
		//Play the sound if exsits
		void playSound(const string& key, bool loop = false);
		//Stop the sound
		void stopSound(const string& key);
		//Returns if sound is playing
		bool isPlaying(const string& key);
		//Return if sounds are nute
		bool isMute();
		//Set the sounds to mute by input
		void mute(bool isMute);
	private:
		bool _isMute;
		SoundsMap _sounds;
		//Get sound by key
		BufferAndSound * getSound(const string& key);
		SoundsManager();
};

