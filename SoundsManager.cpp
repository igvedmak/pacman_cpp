#include "SoundsManager.h"


SoundsManager& SoundsManager::getInstance() {
	static SoundsManager instance;
	return instance;
}

void SoundsManager::addSound(const string& path, int volume) {
	std::unique_ptr<BufferAndSound> bas = std::make_unique<BufferAndSound>();
	bas->_buffer.loadFromFile(path);
	bas->_sound.setBuffer(bas->_buffer);
	bas->_sound.setVolume((float)volume);
	_sounds.insert(std::make_pair(path, std::move(bas)));
}

void SoundsManager::playSound(const string& key, bool loop) {
	if (!_isMute) {
		auto sound = getSound(key);
		if (sound != nullptr) {
			sound->_sound.play();
			sound->_sound.setLoop(loop);
		}
	}
}

void SoundsManager::stopSound(const string& key) {
	auto sound = getSound(key);
	if (sound != nullptr) {
		sound->_sound.stop();
	}
}

bool SoundsManager::isPlaying(const string& key) {
	auto sound = getSound(key);
	if (sound != nullptr) {
		return sound->_sound.getStatus() == sf::SoundSource::Playing;
	}
	return false;
}

bool SoundsManager::isMute()
{
	return _isMute;
}

void SoundsManager::mute(bool isMute) {
	_isMute = isMute;
}

BufferAndSound * SoundsManager::getSound(const string& key) {
	auto it = _sounds.find(key);
	if (it != _sounds.end()) {
		return (*it).second.get();
	}

	return nullptr;
}

SoundsManager::SoundsManager() {}