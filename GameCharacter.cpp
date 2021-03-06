#include "GameCharacter.h"

using namespace gs2d;
using namespace gs2d::math;

const unsigned int GameCharacter::MOVING_DOWN = 0;
const unsigned int GameCharacter::MOVING_LEFT = 1;
const unsigned int GameCharacter::MOVING_RIGHT = 2;
const unsigned int GameCharacter::MOVING_UP = 3;
const unsigned long GameCharacter::m_defaultFrameStride = 150;

GameCharacter::GameCharacter(const Vector2& pos, const str_type::string& spriteName) :
	m_pos(pos),
	m_currentFrameStride(m_defaultFrameStride),
	m_direction(MOVING_UP),
	m_spriteName(spriteName)
{
}

Vector2 GameCharacter::GetPos()
{
	return m_pos;
}

void GameCharacter::Move(const Vector2& dir, const float speed)
{
	m_moveVector += Normalize(dir) * speed;
}

void GameCharacter::FillSpritePtr(SpriteResourceManager& spr, gs2d::VideoPtr video)
{
	m_sprite = spr.GetSprite(video, m_spriteName);
}

void GameCharacter::SetFrameStride(const unsigned long stride)
{
	m_currentFrameStride = stride;
}

void GameCharacter::SetDirection(const Vector2& dir)
{
	SetDirection(GetAngle(dir));
}

void GameCharacter::SetDirection(const float angle)
{
	m_direction = FindDirection(angle);
}

int GameCharacter::FindDirection(const float angle)
{
	if (angle > gs2d::math::constant::PI/4 + gs2d::math::constant::PI/2 && angle < gs2d::math::constant::PI + gs2d::math::constant::PI/4)
	{
		return MOVING_UP;
	}
	else if (angle > gs2d::math::constant::PI/4 + gs2d::math::constant::PI + gs2d::math::constant::PI/2 || angle < gs2d::math::constant::PI/4)
	{
		return MOVING_DOWN;
	}
	else if (angle > gs2d::math::constant::PI/4 && angle < gs2d::math::constant::PI/2 + gs2d::math::constant::PI/4)
	{
		return MOVING_RIGHT;
	}
	else
	{
		return MOVING_LEFT;
	}
}

void GameCharacter::Draw(SpriteResourceManager& spr, VideoPtr video)
{
	m_sprite->SetOrigin(GSEO_CENTER_BOTTOM);
	m_sprite->SetRect(m_frameTimer.Get());
	m_sprite->Draw(m_pos);
}

void GameCharacter::Update(VideoPtr video, InputPtr input, const unsigned long lastFrameDeltaTimeMS)
{
	const float angle = GetAngle(m_moveVector);
	if (m_moveVector.Length() > 0.0f)
	{
		m_direction = FindDirection(angle);
		switch (m_direction)
		{
		case MOVING_UP:
			m_frameTimer.Update(12, 15, m_currentFrameStride);
			break;
		case MOVING_DOWN:
			m_frameTimer.Update(0, 3, m_currentFrameStride);
			break;
		case MOVING_LEFT:
			m_frameTimer.Update(4, 7, m_currentFrameStride);
			break;
		case MOVING_RIGHT:
			m_frameTimer.Update(8, 11, m_currentFrameStride);
			break;
		}
	}
	else
	{
		switch (m_direction)
		{
		case MOVING_UP:
			m_frameTimer.Update(12, 12, m_currentFrameStride);
			break;
		case MOVING_DOWN:
			m_frameTimer.Update(0, 0, m_currentFrameStride);
			break;
		case MOVING_LEFT:
			m_frameTimer.Update(4, 4, m_currentFrameStride);
			break;
		case MOVING_RIGHT:
			m_frameTimer.Update(8, 8, m_currentFrameStride);
			break;
		}
	}
	m_pos += m_moveVector;
	m_moveVector = Vector2(0.0f, 0.0f);
}

str_type::string GameCharacter::GetSpriteName()
{
	return m_spriteName;
}

SpritePtr GameCharacter::GetSprite()
{
	return m_sprite;
}