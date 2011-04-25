#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include "GameCharacter.h"

class Zombie : public GameCharacter
{
	gs2d::math::Vector2 m_wanderDir;
	const float m_speed;
	bool m_dead;

	void FixDirection(gs2d::VideoPtr video);

public:
	Zombie(gs2d::VideoPtr video, const gs2d::math::Vector2& pos, gs2d::str_type::string spriteName);
	void Update(gs2d::VideoPtr video, gs2d::InputPtr input, const unsigned long lastFrameDeltaTimeMS);
	bool IsDead() const;
	void Kill();
	void Draw(SpriteResourceManager& spr, gs2d::VideoPtr video);
};

typedef boost::shared_ptr<Zombie> ZombiePtr;

#endif