#include "Resources.h"

#include <fstream>
#include <iostream>

Resources::Resources()
{
	setTextures();

	m_font.loadFromFile("C:/Windows/Fonts/COOPBL.ttf");

	setMusic();
	
	setSound();
}

void Resources::setTextures()
{
	std::ifstream textureNames;

	textureNames.open("textures.txt");
	if (!textureNames.is_open())
	{
		throw std::runtime_error("Cannot open textures.txt");
	}

	std::string newName;

	for (int texture = 0; !textureNames.eof(); texture++)
	{
		sf::Texture newTexture;
		std::getline(textureNames, newName);

		newTexture.loadFromFile(newName);
		m_textures.push_back(newTexture);
	}
	textureNames.close();
}

void Resources::setMusic()
{
	if (!m_music.openFromFile("backgroundMusic.wav"))
	{
		throw std::runtime_error("Cannot load music");
	}
	m_music.setLoop(true);
	m_music.setVolume(10);
}

void Resources::setSound()
{
	std::ifstream soundNames;

	soundNames.open("sounds.txt");
	if (!soundNames.is_open())
	{
		throw std::runtime_error("Cannot open sounds.txt");
	}

	std::string newName;
	sf::SoundBuffer newSoundBuffer;

	for (int sound = 0; !soundNames.eof(); sound++)
	{
		std::getline(soundNames, newName);

		if (!newSoundBuffer.loadFromFile(newName))
		{
			throw std::runtime_error("Cannot load sound");
		}
		m_soundBuffers.push_back(newSoundBuffer);
	}
	soundNames.close();

	sf::Sound newSound;

	for (int sound = 0; sound < m_soundBuffers.size(); sound++)
	{
		newSound.setBuffer(m_soundBuffers[sound]);
		m_sounds.push_back(newSound);
	}
}

sf::Sprite Resources::getSprite(type object)
{
	return sf::Sprite(m_textures[int(object)]);
}

sf::Text Resources::getText()
{
	sf::Text text;
	text.setFont(m_font);

	return text;
}

void Resources::playSound(gameSounds sound)
{
	m_sounds[int(sound)].play();
}

void Resources::stopSound(gameSounds sound)
{
	m_sounds[int(sound)].stop();
}

void Resources::playMusic()
{
	m_music.play();
}

void Resources::pauseMusic()
{
	m_music.pause();
}

Resources& Resources::getResources()
{
	static Resources resources;
	return resources;
}