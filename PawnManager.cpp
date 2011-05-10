#include "PawnManager.h"
#include "StateManager.h"

using namespace gs2d;
using namespace gs2d::math;

const int PawnManager::GOAL_SCORE = 10;

PawnManager::PawnManager(VideoPtr video, BallPtr ball) :
	m_explosionSprite(GS_L("explosion.png"))
{
	const Vector2 screenSize(video->GetScreenSizeF());
	const Vector2 areaSize(screenSize.x/2.0f, screenSize.y);

	int id = 0;
	m_pawns.push_back(
		PawnPtr(new Pawn(Rect2Df(Vector2(0, 0), areaSize),
			ControllerPtr(new PlayerTouchController(ball)), ball,
			Vector2(1.0f, 0.5f), id++)
		)
	);

	m_pawns.push_back(
		PawnPtr(new Pawn(Rect2Df(Vector2(screenSize.x/2.0f, 0), areaSize),
			ControllerPtr(new PlayerTouchController(ball)), ball,
			Vector2(0.0f, 0.5f), id++)
		)
	);
	m_ball = ball;
}

void PawnManager::Update(VideoPtr video, InputPtr input, AudioPtr audio, EffectManagerPtr fxManager,
						 const unsigned long lastFrameElapsedTimeMS, SpriteResourceManager& spr)
{
	const std::size_t size = m_pawns.size();
	for (std::size_t t = 0; t<size; t++)
	{
		m_pawns[t]->Update(video, input, audio, fxManager, lastFrameElapsedTimeMS, spr);
		ManageScore(t, video, audio, fxManager, spr);
	}
	if (m_ball->MustExplode())
	{
		const float explosionSize = m_ball->GetRadius(spr, video) * 4.0f;
		fxManager->Add(TemporaryEffectPtr(new SingleParticle(video, GS_L("explosion.png"), m_ball->GetPos(), 0.0f, 800, 0.0f,
			Vector2(explosionSize, explosionSize), 1.0f, false, false, Randomizer::Float(360.0f))));
		m_pawns[m_ball->GetCurrentArea()]->SetScore(0);
		m_ball->Reset(video);
	}
}

void PawnManager::AddToScore(const int pawn, const int score)
{
	if (pawn >= 0)
	{
		m_pawns[pawn]->AddToScore(score);
	}
}

void PawnManager::ManageScore(const std::size_t idx, VideoPtr video, AudioPtr audio, EffectManagerPtr fxManager, SpriteResourceManager& spr)
{
	if (m_pawns[idx]->GoalScored(video, spr))
	{
		StateManager::m_aud.GetSample(audio, GS_L("score.ogg"))->Play();
		SpritePtr ballSprite = spr.GetSprite(video, m_ball->GetSpriteName());
		fxManager->Add(TemporaryEffectPtr(new SingleParticle(video, m_ball->GetSpriteName(), m_ball->GetPos(), 400.0f, 600, 1.2f,
					   ballSprite->GetBitmapSizeF(), 0.8f, false)));
		m_ball->Reset(video);
		m_pawns[idx]->AddToScore(GOAL_SCORE);
	}
}

void PawnManager::Draw(VideoPtr video, SpriteResourceManager& spr)
{
	const std::size_t size = m_pawns.size();
	for (std::size_t t = 0; t<size; t++)
	{
		m_pawns[t]->DrawScore(video);
	}
	for (std::size_t t = 0; t<size; t++)
	{
		m_pawns[t]->DrawGoal(video, spr);
	}
	for (std::size_t t = 0; t<size; t++)
	{
		m_pawns[t]->Draw(video, spr);
	}
}
