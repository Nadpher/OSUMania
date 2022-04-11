#ifndef OSUMANIA_UTIL_H
#define OSUMANIA_UTIL_H

#include <vector>

#include "Scenes/Note.h"

namespace nadpher
{
	// uses bubble sort, can be improved
	static void sortNotes(std::vector<Note>& vec)
	{
		size_t len = vec.size();
		for (int i = 0; i < len; ++i)
		{
			for (int j = i + 1; j < len; ++j)
			{
				if (vec[i].getTimePosition() > vec[j].getTimePosition())
				{
					std::swap(vec[i], vec[j]);
				}
			}
		}
	}
}

#endif
