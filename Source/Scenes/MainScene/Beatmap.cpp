#include "../../Game.h"
#include "../../Input.h"

#include "Beatmap.h"

#include <spdlog/spdlog.h>

#include <fstream>
#include <sstream>

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

	void Beatmap::clearLanes()
	{
		for (Lane& lane : lanes_)
		{
			lane.clear();
		}
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

			lanes_[lane].addNote({ position, velocity, lane });
		}
	}

	void Beatmap::update()
	{
		conductor_.update(song_.getPlayingOffset().asSeconds());

		for (Lane& lane : lanes_)
		{
			lane.update(conductor_);
		}

		// need to refactor this, beatmap shouldn't call to pop note
		if (Input::isKeyDown(sf::Keyboard::Z))
		{
			lanes_[0].hitNote(conductor_);
		}

		if (Input::isKeyDown(sf::Keyboard::X))
		{
			lanes_[1].hitNote(conductor_);
		}

		if (Input::isKeyDown(sf::Keyboard::N))
		{
			lanes_[2].hitNote(conductor_);
		}

		if (Input::isKeyDown(sf::Keyboard::M))
		{
			lanes_[3].hitNote(conductor_);
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