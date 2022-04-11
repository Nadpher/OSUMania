#include "../Game.h"
#include "../Input.h"
#include "../Util.h"

#include "Beatmap.h"

#include <spdlog/spdlog.h>

#include <fstream>
#include <sstream>

namespace nadpher
{
	Beatmap::Beatmap()
	{

	}

	// NEEDS to be split up in different functions
	bool Beatmap::readFromDisk(const std::string& folderPath)
	{
		notes_.clear();

		std::ifstream beatmapFile(folderPath + "/song.beatmap", std::ios::in);

		if (!song_.openFromFile(folderPath + "/song.ogg"))
		{
			spdlog::error("Couldn't open song.ogg file in {}", folderPath);
			return false;
		}

		// this is so fucking bad
		if (beatmapFile.is_open())
		{
			float bpm = 0.0f;
			float offset = 0.0f;

			std::string line;
			std::string fileString = "";

			// translates file to string
			while (std::getline(beatmapFile, line))
			{
				fileString += line + '\n';
			}

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

			// reads time positions in file
			std::stringstream timePositions(fileString.substr(fileString.find(']') + 2));

			while (std::getline(timePositions, line))
			{
				size_t separator = line.find(',');
				float position = std::stof(line.substr(0, separator));
				unsigned int lane = std::stoul(line.substr(separator + 1, 1));

				separator = line.find(',', separator + 1);
				float velocity = std::stof(line.substr(separator + 1));

				notes_.push_back({ position, velocity, lane });
			}

			// notes vector needs to be sorted for some cool stuff i dont remember lol
			// either way it's best to keep it sorted for ease of use
			sortNotes(notes_);
		}
		else
		{
			spdlog::error("Couldn't open song.beatmap file in {}", folderPath);
			return false;
		}

		path_ = folderPath;
		
		return true;
	}

	bool Beatmap::writeToDisk()
	{
		std::ofstream outputFile(path_ + "/song.beatmap", std::ios::out);
		if (outputFile.is_open())
		{

			outputFile << "\n[TIME POSITIONS]";
			for (const Note& note : notes_)
			{
				outputFile << note.getTimePosition() << ',' << note.getLane() << ',' << note.getVelocity() << '\n';
			}
		}
		else
		{
			return false;
		}

		return true;
	}

	// finds first note of lane and returns judge value
	Note::HitInfo Beatmap::hitNote(unsigned int lane)
	{
		for (Note& note : notes_)
		{
			if (note.getLane() == lane && note.isAlive())
			{
				return note.judge(conductor_);
			}
		}

		return {};
	}

	// checks if all notes are dead
	bool Beatmap::empty()
	{
		for (const Note& note : notes_)
		{
			if (note.isAlive())
			{
				return false;
			}
		}

		return true;
	}

	Note::HitInfo Beatmap::update()
	{
		conductor_.update(song_.getPlayingOffset().asSeconds());

		Note::HitInfo lastHit = { false, 0 };

		// missed notes
		for (Note& note : notes_)
		{
			if (note.isAlive())
			{
				if (!note.update(conductor_))
				{
					lastHit.hit = true;
				}
			}
		}

		return lastHit;
	}

	void Beatmap::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const Note& note : notes_)
		{
			if (note.isAlive())
			{
				target.draw(note, states);
			}
		}
	}
}