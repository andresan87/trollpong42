#include "Zombie.h"
#include "Util.h"

using namespace gs2d;
using namespace gs2d::math;

Zombie::Zombie(VideoPtr video, const Vector2& pos, str_type::string spriteName) :
	GameCharacter(pos, spriteName),
	m_wanderDir(0, 0),
	m_speed(25.0f),
	m_dead(false)
{
	SetFrameStride(125);
}

void Zombie::Update(VideoPtr video, InputPtr input, const unsigned long lastFrameDeltaTimeMS)
{
	if (m_wanderDir == Vector2(0, 0))
	{
		const float dirX = 1 - Randomizer::Float(2.0f);
		const float dirY = 1 - Randomizer::Float(2.0f);
		m_wanderDir = Normalize(Vector2(dirX, dirY));
	}
	Move(m_wanderDir, m_speed / AssertFPS(video));
	GameCharacter::Update(video, input, lastFrameDeltaTimeMS);
	FixDirection(video);
}

void Zombie::FixDirection(VideoPtr video)
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

void Zombie::Draw(SpriteResourceManager& spr, VideoPtr video)
{
	DrawShadow(video, spr.GetSprite(video, GS_L("char_shadow.png")), m_pos, 13.0f);
	GameCharacter::Draw(spr, video);
}

bool Zombie::IsDead() const
{
	return m_dead;
}

void Zombie::Kill()
{
	m_dead = true;
}
