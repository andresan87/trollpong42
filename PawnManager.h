#ifndef PAWN_MANAGER_H_
#define PAWN_MANAGER_H_

#include "../gs2d/src/gs2dframework.h"
#include "Controller.h"
#include "SpriteResourceManager.h"
#include <vector>

class PawnManager
{
	std::vector<PawnPtr> m_pawns;
	BallPtr m_ball;
	gs2d::str_type::string m_explosionSprite;

	void ManageScore(const std::size_t idx, gs2d::VideoPtr video, gs2d::AudioPtr audio, EffectManagerPtr fxManager, SpriteResourceManager& spr);

	static std::vector<gs2d::math::Rect2Df> m_forbiddenAreas;

public:
	static const float GOAL_SCORE;

	PawnManager(gs2d::VideoPtr video, BallPtr ball);
	inline static const std::vector<gs2d::math::Rect2Df>& GetForbiddenAreas() { return m_forbiddenAreas; };
	void Update(gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio, EffectManagerPtr fxManager, const unsigned long lastFrameElapsedTimeMS, SpriteResourceManager& spr);
	void Draw(gs2d::VideoPtr video, SpriteResourceManager& spr);
	void AddToScore(const int pawn, const float score);
};

typedef boost::shared_ptr<PawnManager> PawnManagerPtr;

#endif