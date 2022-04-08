#ifndef OSUMANIA_EDIT_SCENE_H
#define OSUMANIA_EDIT_SCENE_H

#include "../Scene.h"
#include "../Beatmap.h"

#include <string>

namespace nadpher
{
	class EditScene : public Scene
	{
	public:
		EditScene(const std::string& path = "");

		bool update() override;
		void end() override;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:

		Beatmap beatmap_;
	};
}

#endif

