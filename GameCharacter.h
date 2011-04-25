#ifndef GAME_CHARACTER_H_
#define GAME_CHARACTER_H_

#include "../gs2d/src/gs2dframework.h"
#include "FrameTimer.h"
#include "SpriteResourceManager.h"

class GameCharacter
{
protected:
	static const unsigned int MOVING_DOWN;
	static const unsigned int MOVING_LEFT;
	static const unsigned int MOVING_RIGHT;
	static const unsigned int MOVING_UP;

	static const unsigned long m_defaultFrameStride;

	gs2d::str_type::string m_spriteName;
	gs2d::math::Vector2 m_pos;

	FrameTimer m_frameTimer;
	unsigned long m_currentFrameStride;
	unsigned int m_direction;

	gs2d::math::Vector2 m_moveVector;

public:
	GameCharacter(const gs2d::math::Vector2& pos, const gs2d::str_type::string& m_spriteName);
	gs2d::math::Vector2 GetPos();
	void Move(const gs2d::math::Vector2& dir, const float speed);
	void SetFrameStride(const unsigned long stride);
	void SetDirection(const gs2d::math::Vector2& dir);
	void SetDirection(const float angle);
	int FindDirection(const float angle);
	void Draw(SpriteResourceManager& spr, gs2d::VideoPtr video);
	void Update(gs2d::VideoPtr video, gs2d::InputPtr input, const unsigned long lastFrameDeltaTimeMS);
	gs2d::str_type::string GetSpriteName();
};

#endif