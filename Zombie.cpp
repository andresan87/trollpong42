#include "Zombie.h"

using namespace gs2d;
using namespace gs2d::math;

Zombie::Zombie(VideoPtr video, const gs2d::math::Vector2& pos, gs2d::SpritePtr sprite) :
	GameCharacter(pos, sprite),
	m_wanderDir(0, 0),
	m_speed(25.0f),
	m_dead(false)
{
}

void Zombie::Update(gs2d::VideoPtr video, gs2d::InputPtr input, const unsigned long lastFrameDeltaTimeMS)
{
	if (m_wanderDir == Vector2(0, 0))
	{
		const float dirX = 1 - Randomizer::Float(2.0f);
		const float dirY = 1 - Randomizer::Float(2.0f);
		m_wanderDir = Normalize(Vector2(dirX, dirY));
	}
	Move(m_wanderDir, m_speed / video->GetFPSRate());
	GameCharacter::Update(video, input, lastFrameDeltaTimeMS);
	FixDirection(video);
}

void Zombie::FixDirection(gs2d::VideoPtr video)
{
	const Vector2 screenSize = video->GetScreenSizeF();
	if (m_pos.x > screenSize.x || m_pos.x < 0.0f)
	{
		m_wanderDir.x *= -1.0f;
	}
	if (m_pos.y > screenSize.y || m_pos.y < 0.0f)
	{
		m_wanderDir.y *= -1.0f;
	}
}

bool Zombie::IsDead() const
{
	return m_dead;
}

void Zombie::Kill()
{
	m_dead = true;
}