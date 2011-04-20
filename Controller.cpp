#include "Controller.h"
#include "Util.h"

using namespace gs2d;
using namespace gs2d::math;

PlayerTouchController::PlayerTouchController(BallPtr ball)
{
	m_ball = ball;
}

Vector2 HasTouchHit(InputPtr input, VideoPtr video)
{
	for (unsigned int t=0; t<input->GetMaxTouchCount(); t++)
	{
		if (input->GetTouchState(t) == GSKS_HIT)
		{
			return input->GetTouchPos(t, video);
		}
	}
	return GS_NO_TOUCH;
}

Vector2 HasTouchHitInArea(const Rect2Df& area, InputPtr input, VideoPtr video)
{
	for (unsigned int t=0; t<input->GetMaxTouchCount(); t++)
	{
		if (input->GetTouchState(t) == GSKS_HIT)
		{
			const Vector2 currentTouch = input->GetTouchPos(t, video);
			if (IsInArea(currentTouch, area))
			{
				return currentTouch;
			}
		}
	}
	return GS_NO_TOUCH;
}

Vector2 GetTouchMoveInArea(const Rect2Df& area, InputPtr input, VideoPtr video)
{
	for (unsigned int t=0; t<input->GetMaxTouchCount(); t++)
	{
		const Vector2 currentTouch = input->GetTouchPos(t, video);
		if (currentTouch != GS_NO_TOUCH)
		{
			if (IsInArea(currentTouch, area))
			{
				return input->GetTouchMove(t);
			}
		}
	}
	return Vector2(0, 0);
}

void PlayerTouchController::Update(Pawn *pawn, VideoPtr video, InputPtr input, EffectManagerPtr fxManager, const unsigned long lastFrameElapsedTimeMS) const
{
	if (m_ball->m_dir == Vector2(0, 0))
	{
		Vector2 touchHit;
		if ((touchHit = HasTouchHit(input, video)) != GS_NO_TOUCH)
		{
			m_ball->m_dir = touchHit - m_ball->m_pos;
		}
	}

	const Vector2 touchPos = HasTouchHitInArea(pawn->m_area, input, video);
	if (touchPos != GS_NO_TOUCH)
	{
		fxManager->Add(TemporaryEffectPtr(new SingleParticle(video, pawn->m_sprite, pawn->m_pos, 600.0f, 400, 1.1f,
					   pawn->m_sprite->GetBitmapSizeF(), 0.5f, false)), false);
		pawn->m_pos = touchPos;
		fxManager->Add(TemporaryEffectPtr(new SingleParticle(video, pawn->m_sprite, pawn->m_pos,-600.0f, 300,-1.1f,
					   pawn->m_sprite->GetBitmapSizeF() * 1.5f, 1.0f, true)), false);
	}
}
