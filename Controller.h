#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "GameEntity.h"

class Controller
{
public:
	virtual void Update(Pawn *pawn, gs2d::VideoPtr video, gs2d::InputPtr input, EffectManagerPtr fxManager,
		const unsigned long lastFrameElapsedTimeMS, SpriteResourceManager& spr,
		const std::vector<gs2d::math::Rect2Df>& forbiddenAreas) const = 0;
};

typedef boost::shared_ptr<Controller> ControllerPtr;

class PlayerTouchController : public Controller
{
	BallPtr m_ball;

public:
	PlayerTouchController(BallPtr ball);
	void Update(Pawn *pawn, gs2d::VideoPtr video, gs2d::InputPtr input, EffectManagerPtr fxManager,
		const unsigned long lastFrameElapsedTimeMS, SpriteResourceManager& spr,
		const std::vector<gs2d::math::Rect2Df>& forbiddenAreas) const;
};

typedef boost::shared_ptr<PlayerTouchController> PlayerTouchControllerPtr;

#endif