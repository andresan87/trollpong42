#include "PawnManager.h"

using namespace gs2d;
using namespace gs2d::math;

const int PawnManager::GOAL_SCORE = 10;

PawnManager::PawnManager(VideoPtr video, SpritePtr pawn0, SpritePtr pawn1, gs2d::SpritePtr goal, BallPtr ball,
						 SpritePtr shadowSprite, SpritePtr explosionSprite) :
	m_explosionSprite(explosionSprite)
{
	const Vector2 screenSize(video->GetScreenSizeF());
	const Vector2 areaSize(screenSize.x/2.0f, screenSize.y);

	int id = 0;
	m_pawns.push_back(
		PawnPtr(new Pawn(pawn0, Rect2Df(Vector2(0, 0), areaSize),
			ControllerPtr(new PlayerTouchController(ball)), ball,
			Vector2(1.0f, 0.5f), goal, id++, shadowSprite)
		)
	);

	m_pawns.push_back(
		PawnPtr(new Pawn(pawn0, Rect2Df(Vector2(screenSize.x/2.0f, 0), areaSize),
			ControllerPtr(new PlayerTouchController(ball)), ball,
			Vector2(0.0f, 0.5f), goal, id++, shadowSprite)
		)
	);
	m_ball = ball;
}

void PawnManager::Update(VideoPtr video, InputPtr input, EffectManagerPtr fxManager, const unsigned long lastFrameElapsedTimeMS)
{
	const std::size_t size = m_pawns.size();
	for (std::size_t t = 0; t<size; t++)
	{
		m_pawns[t]->Update(video, input, fxManager, lastFrameElapsedTimeMS);
		ManageScore(t, video, fxManager);
	}
	if (m_ball->MustExplode())
	{
		const float explosionSize = m_ball->GetRadius() * 4.0f;
		fxManager->Add(TemporaryEffectPtr(new SingleParticle(video, m_explosionSprite, m_ball->GetPos(), 0.0f, 800, 0.0f,
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

void PawnManager::ManageScore(const std::size_t idx, VideoPtr video, EffectManagerPtr fxManager)
{
	if (m_pawns[idx]->GoalScored(video))
	{
		fxManager->Add(TemporaryEffectPtr(new SingleParticle(video, m_ball->GetSprite(), m_ball->GetPos(), 400.0f, 600, 1.2f,
					   m_ball->GetSprite()->GetBitmapSizeF(), 0.8f, false)));
		m_ball->Reset(video);
		m_pawns[idx]->AddToScore(GOAL_SCORE);
	}
}

void PawnManager::Draw(VideoPtr video)
{
	const std::size_t size = m_pawns.size();
	for (std::size_t t = 0; t<size; t++)
	{
		m_pawns[t]->DrawScore(video);
	}
	for (std::size_t t = 0; t<size; t++)
	{
		m_pawns[t]->DrawGoal(video);
	}
	for (std::size_t t = 0; t<size; t++)
	{
		m_pawns[t]->Draw(video);
	}
}