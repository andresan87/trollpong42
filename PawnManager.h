#ifndef PAWN_MANAGER_H_
#define PAWN_MANAGER_H_

#include "../gs2d/src/gs2dframework.h"
#include "Controller.h"
#include <vector>

class PawnManager
{
	std::vector<PawnPtr> m_pawns;
	BallPtr m_ball;
	gs2d::SpritePtr m_explosionSprite;

	void ManageScore(const std::size_t idx, gs2d::VideoPtr video, EffectManagerPtr fxManager);

public:
	static const int GOAL_SCORE;

	PawnManager(gs2d::VideoPtr video, gs2d::SpritePtr pawn0, gs2d::SpritePtr pawn1, gs2d::SpritePtr goal,
				BallPtr ball, gs2d::SpritePtr shadowSprite, gs2d::SpritePtr explosionSprite);
	void Update(gs2d::VideoPtr video, gs2d::InputPtr input, EffectManagerPtr fxManager, const unsigned long lastFrameElapsedTimeMS);
	void Draw(gs2d::VideoPtr video);
	void AddToScore(const int pawn, const int score);
};

typedef boost::shared_ptr<PawnManager> PawnManagerPtr;

#endif