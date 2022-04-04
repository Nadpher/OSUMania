#include "../../Game.h"
#include "../../Input.h"

#include "Beatmap.h"

#include <spdlog/spdlog.h>

#include <fstream>
#include <sstream>

namespace nadpher
{
	Beatmap::Beatmap()
		  : score_(0)
	{
		sf::Vector2u gameBounds = Game::getBounds();
	}

	bool Beatmap::readFromDisk(const std::string& folderPath)
	{
		score_ = 0;
		std::ifstream beatmapFile(folderPath + "/song.beatmap", std::ios::in);

		// this is so fucking bad
		if (beatmapFile.is_open())
		{
			float bpm = 0.0f;
			float offset = 0.0f;
			float velocity = 0.0f;

			std::string line;
			std::string fileString = "";

			// translates file to string
			while (std::getline(beatmapFile, line))
			{
				fileString += line + '\n';
			}
			fileString_ = fileString;
			
			// these are super sketchy
			size_t pos = fileString.find("BPM=");
			if (pos != std::string::npos)
			{
				// 4 is the length of BPM=
				bpm = std::stof(fileString.substr(pos + 4, fileString.find('\n')));
			}

			pos = fileString.find("OFFSET=");
			if (pos != std::string::npos)
			{
				// 7 is the length of OFFSET=
				offset = std::stof(fileString.substr(pos + 7, fileString.find('\n')));
			}

			conductor_.init(offset, bpm);
			loadTimePositions();
		}
		else
		{
			spdlog::error("Couldn't open song.beatmap file in {}", folderPath);
			return false;
		}

		if (!song_.openFromFile(folderPath + "/song.ogg"))
		{
			spdlog::error("Couldn't open song.ogg file in {}", folderPath);
			return false;
		}
		
		return true;
	}

	void Beatmap::loadTimePositions()
	{
		std::stringstream timePositions(fileString_.substr(fileString_.find(']') + 2));

		std::string line;
		while (std::getline(timePositions, line))
		{
			size_t separator = line.find(',');
			float position = std::stof(line.substr(0, separator));
			unsigned int lane = std::stoul(line.substr(separator + 1, 1));

			separator = line.find(',', separator + 1);
			float velocity = std::stof(line.substr(separator + 1));

			notes_.push_back({ position, velocity, lane });
		}
	}

	Note::HitInfo Beatmap::update()
	{
		conductor_.update(song_.getPlayingOffset().asSeconds());

		Note::HitInfo lastHit = { false, 0 };

		if (empty())
		{
			static float newVolume = song_.getVolume() / 2.0f;
			song_.setVolume(newVolume);
			return lastHit;
		}

		// missed notes
		for (Note& note : notes_)
		{
			if (!note.update(conductor_))
			{
				lastHit.hit = true;
				notes_.pop_front();
			}
		}

		// need to implement system
		// to convert raw input into high level commands
		/*if (Input::isKeyDown(sf::Keyboard::Z))
		{
			lastHit = lanes_[0].hitNote(conductor_);
			score_ += lastHit.score;
		}

		if (Input::isKeyDown(sf::Keyboard::X))
		{
			lastHit = lanes_[1].hitNote(conductor_);
			score_ += lastHit.score;
		}

		if (Input::isKeyDown(sf::Keyboard::N))
		{
			lastHit = lanes_[2].hitNote(conductor_);
			score_ += lastHit.score;
		}

		if (Input::isKeyDown(sf::Keyboard::M))
		{
			lastHit = lanes_[3].hitNote(conductor_);
			score_ += lastHit.score;
		}*/

		return lastHit;
	}

	void Beatmap::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const Note& note : notes_)
		{
			target.draw(note);
		}
	}
}