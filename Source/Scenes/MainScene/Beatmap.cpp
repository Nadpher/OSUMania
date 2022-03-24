#include "../../Game.h"
#include "../../Input.h"

#include "Beatmap.h"

#include <spdlog/spdlog.h>

#include <fstream>

namespace nadpher
{
	Beatmap::Beatmap()
		: judgementLine_(sf::LinesStrip, 2)
	{
		judgementLine_[0].position = { 0.0f, judgementLinePosition };
		judgementLine_[1].position = { (float)Game::getBounds().x, judgementLinePosition };
	}

	bool Beatmap::init(const std::string& folderPath)
	{
		std::ifstream beatmapFile(folderPath + "song.beatmap");

		// this is so fucking bad
		if (beatmapFile.is_open())
		{
			bool general = true;
			std::string line;

			float bpm = 0.0f;
			float offset = 0.0f;
			float velocity = 0.0f;
			while (std::getline(beatmapFile, line))
			{
				if (line.empty()) continue;

				if (general)
				{
					if (line == "[TIME POSITIONS]")
					{
						general = false;
						continue;
					}

					auto it = line.find("BPM=");
					if (it != std::string::npos)
					{
						it += line.find('=') + 1;
						std::string value = line.substr(it);
						bpm = std::stof(value);
						continue;
					}

					it = line.find("VELOCITY=");
					if (it != std::string::npos)
					{
						it += line.find('=') + 1;
						std::string value = line.substr(it);
						velocity = std::stof(value);
						continue;
					}

					it = line.find("OFFSET=");
					if (it != std::string::npos)
					{
						it += line.find('=') + 1;
						std::string value = line.substr(it);
						offset = std::stof(value);
						continue;
					}
				}
				else
				{
					conductor_.init(offset, bpm);

					unsigned int lane;
					float timePosition;
					
					size_t pos = line.find(',') + 1;
					std::string value = line.substr(0, pos);
					timePosition = std::stof(value);
					value = line.substr(pos, 1);
					lane = std::stoul(value);

					lanes_[lane].addNote({conductor_, timePosition, velocity, lane});
				}
			}
		}
		else
		{
			spdlog::error("Couldn't open song.beatmap file in {}", folderPath);
			return false;
		}

		if (!song_.openFromFile(folderPath + "song.ogg"))
		{
			spdlog::error("Couldn't open song.ogg file in {}", folderPath);
			return false;
		}

		return true;
	}

	void Beatmap::update()
	{
		conductor_.update(song_.getPlayingOffset().asSeconds());

		for (Lane& lane : lanes_)
		{
			lane.update();
		}

		// need to refactor this, beatmap shouldn't call to pop note
		if (Input::isKeyDown(sf::Keyboard::Z))
		{
			if (lanes_[0].judgeNote(conductor_))
			{
				lanes_[0].popNote();
			}
		}

		if (Input::isKeyDown(sf::Keyboard::X))
		{
			if (lanes_[1].judgeNote(conductor_))
			{
				lanes_[1].popNote();
			}
		}

		if (Input::isKeyDown(sf::Keyboard::N))
		{
			if (lanes_[2].judgeNote(conductor_))
			{
				lanes_[2].popNote();
			}
		}

		if (Input::isKeyDown(sf::Keyboard::M))
		{
			if (lanes_[3].judgeNote(conductor_))
			{
				lanes_[3].popNote();
			}			
		}
	}

	void Beatmap::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(judgementLine_);

		for (const Lane& lane : lanes_)
		{
			target.draw(lane);
		}
	}
}