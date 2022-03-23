#include "Beatmap.h"

#include <spdlog/spdlog.h>

#include <fstream>

namespace nadpher
{
	bool Beatmap::init(const std::string& folderPath)
	{
		std::ifstream beatmapFile(folderPath + "song.beatmap");
		if (beatmapFile.is_open())
		{
			// read file
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

	void Beatmap::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{

	}
}