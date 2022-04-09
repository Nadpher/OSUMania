#ifndef OSUMANIA_MAIN_SCENE_H
#define OSUMANIA_MAIN_SCENE_H

#include "../Scene.h"

namespace nadpher
{
	class MainScene : public Scene
	{
	public:
		void enter() override;
		bool update() override;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		static std::string& getPath() { return selectedMapPath_; };

	private:

		static std::string selectedMapPath_;

		bool drawGui();
		std::string openBeatmap();
	};
}

#endif

