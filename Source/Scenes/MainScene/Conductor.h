#ifndef OSUMANIA_CONDUCTOR_H
#define OSUMANIA_CONDUCTOR_H

namespace sf
{
	class Music;
}

namespace nadpher
{
	class Conductor
	{
	public:
		Conductor(float duration, float offset, float bpm = 120.0f);

		bool update(float songPosition);

		float getCrotchet() const { return crotchet_; }
		float getBPM() const { return bpm_; }

	private:

		float offset_;
		float bpm_;
		float crotchet_;
		float songPosition_;
	};
}

#endif

