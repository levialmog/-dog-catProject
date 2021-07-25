#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include "Macros.h"

class Resources
{
public:
	//d-tor:
	~Resources() = default;

	//other function:
	static Resources& getResources();
	sf::Sprite getSprite(type);
	sf::Text getText();
	void playSound(gameSounds);
	void playMusic();
	void pauseMusic();
	void stopSound(gameSounds);

private:
	//c-tor:
	Resources();

	//members:
	std::vector<sf::Texture > m_textures;
	sf::Font m_font;
	sf::Music m_music;
	std::vector<sf::SoundBuffer> m_soundBuffers;
	std::vector<sf::Sound> m_sounds;

	//private function:
	void setTextures();
	void setSound();
	void setMusic();
};