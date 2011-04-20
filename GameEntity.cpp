#include "GameEntity.h"
#include "Controller.h"
#include "Util.h"

using namespace gs2d;
using namespace math;

Vector2 GameEntity::GetPos() const
{
	return m_pos;
}

void GameEntity::AddToPos(const Vector2& v)
{
	m_pos += v;
}

void Ball::TimeBomb::SetArea(const int area)
{
	if (area != m_area)
	{
		m_area = area;
		m_elapsedTime = 0;
	}
}

Ball::TimeBomb::TimeBomb() :
	m_elapsedTime(0),
	BOMB_TIME(10000),
	NO_AREA(-1),
	m_area(NO_AREA)
{
}

void Ball::TimeBomb::Reset()
{
	m_area = NO_AREA;
	m_elapsedTime = 0;
}

void Ball::TimeBomb::Update(const Ball* pBall, const unsigned long lastFrameElapsedTimeMS, const int area)
{
	if (pBall->GetDir() != Vector2(0, 0))
		SetArea(area);
	else
		Reset();
	m_elapsedTime += Min(lastFrameElapsedTimeMS, static_cast<unsigned long>(1000));
}

bool Ball::TimeBomb::MustExplode(const Ball* pBall) const
{
	if (pBall->GetDir() != Vector2(0,0))
		return (m_elapsedTime > BOMB_TIME);
	else
		return false;
}

int Ball::TimeBomb::GetArea() const
{
	return m_area;
}

float Ball::TimeBomb::GetExplosionBiasF() const
{
	if (m_area != NO_AREA)
		return (static_cast<float>(m_elapsedTime) / static_cast<float>(BOMB_TIME));
	else
		return 0.0f;
}

GS_BYTE Ball::TimeBomb::GetExplosionBias() const
{
	return static_cast<GS_BYTE>(GetExplosionBiasF() * 255.0f);
}

Ball::Ball(SpritePtr sprite, SpritePtr highlight, SpritePtr shadowSprite, VideoPtr video) :
	m_angle(0),
	m_sprite(sprite),
	m_highlight(highlight),
	m_dir(0, 0),
	m_speed(300.0f),
	m_lastTouchOwnerId(-1),
	m_shadowSprite(shadowSprite),
	m_currentArea(-1)
{
	m_pos = video->GetScreenSizeF()/2.0f;
}

void Ball::SetLastTouchOwnerId(const int id)
{
	m_lastTouchOwnerId = id;
}

int Ball::GetCurrentArea() const
{
	return m_currentArea;
}

int Ball::GetTouchOwnerId() const
{
	return m_lastTouchOwnerId;
}

Vector2 Ball::GetPos() const
{
	return m_pos;
}

SpritePtr Ball::GetSprite()
{
	return m_sprite;
}

void Ball::Reset(VideoPtr video)
{
	m_lastTouchOwnerId = -1;
	m_pos = video->GetScreenSizeF() / 2.0f;
	m_dir = Vector2(0.0f, 0.0f);
	m_timeBomb.Reset();
}

void Ball::LockInside(VideoPtr video)
{
	const Vector2 ballSize(GetRadius(), GetRadius());
	const Vector2 min(ballSize);
	const Vector2 max(video->GetScreenSizeF()-ballSize);

	if (m_pos.x < min.x || m_pos.x > max.x)
		m_dir.x *= -1.0f;
	if (m_pos.y < min.y || m_pos.y > max.y)
		m_dir.y *= -1.0f;

	Clamp(m_pos, GetRadius(), Rect2Df(Vector2(0,0), video->GetScreenSizeF()));
}

Vector2 Ball::GetDir() const
{
	return m_dir;
}

float Ball::GetRadius() const
{
	return m_sprite->GetBitmapSizeF().x / 2.0f;
}

void Ball::Draw(VideoPtr video)
{
	m_sprite->Draw(m_pos, GS_WHITE, m_angle);

	video->SetAlphaMode(GSAM_ADD);
	const int angle = static_cast<int>(m_angle) % 10;

	DrawShadow(video, m_shadowSprite, m_pos, GetRadius());
	const GS_BYTE explosionColor = 255-m_timeBomb.GetExplosionBias();
	m_highlight->Draw(m_pos, GS_COLOR(255, 255, explosionColor, explosionColor), static_cast<float>(angle));
	video->SetAlphaMode(GSAM_PIXEL);
}

void Ball::Update(VideoPtr video, InputPtr input, EffectManagerPtr fxManager, const unsigned long lastFrameElapsedTimeMS)
{
	m_pos += Normalize(m_dir) * (m_speed/AssertFPS(video));
	m_angle += (m_speed/AssertFPS(video)) * 49.0f;
	LockInside(video);
	m_timeBomb.Update(this, lastFrameElapsedTimeMS, GetCurrentArea());
}

bool Ball::MustExplode() const
{
	return m_timeBomb.MustExplode(this);
}

Pawn::Goal::Goal(SpritePtr sprite, Vector2 normalizedPos) :
	m_sprite(sprite),
	m_normalizedPos(normalizedPos)
{
}

void Pawn::Goal::Draw(VideoPtr video) const
{
	const Vector2 bitmapSize(m_sprite->GetBitmapSizeF());
	const Vector2 screenSize(video->GetScreenSizeF());
	const Vector2 pos = m_normalizedPos * screenSize;
	const Vector2 goalDir = Normalize((screenSize/2.0f) - pos) * bitmapSize.y;
	m_sprite->Stretch(pos, pos + goalDir, bitmapSize.x, GS_BLACK, GS_BLACK);
}

float Pawn::Goal::GetRadius() const
{
	return m_sprite->GetBitmapSizeF().x / 2.0f;
}

Vector2 Pawn::Goal::GetNormalizedPos() const
{
	return m_normalizedPos;
}

Pawn::Pawn(SpritePtr sprite, const Rect2Df &area, ControllerPtr controller, BallPtr ball,
		const Vector2& goalNormalizedPos, SpritePtr goalSprite, const int uniqueId, SpritePtr shadowSprite) :
	m_sprite(sprite),
	m_area(area),
	m_controller(controller),
	m_ball(ball),
	m_goal(goalSprite, goalNormalizedPos),
	m_uniqueId(uniqueId),
	m_score(0),
	m_scoreFont(GS_L("Arcade80.fnt")),
	m_scorePosOffset(32.0f),
	m_shadowSprite(shadowSprite)
{
	m_pos = Vector2(area.pos + (area.size / 2.0f));
}

void Pawn::Draw(VideoPtr video)
{
	DrawShadow(video, m_shadowSprite, m_pos, GetRadius());
	m_sprite->Draw(m_pos);
}

void Pawn::DrawGoal(VideoPtr video)
{
	m_goal.Draw(video);
}

void Pawn::DrawScore(VideoPtr video)
{
	const Vector2 screenSize(video->GetScreenSizeF());
	Vector2 pos(screenSize.x / 2.0f, 0.0f);

	str_type::stringstream ss;
	ss << m_score;
	const Vector2 textSize(video->ComputeTextBoxSize(m_scoreFont, ss.str()));
	if (pos.x + textSize.x > m_area.pos.x + m_area.size.x)
		pos.x -= textSize.x + m_scorePosOffset;
	else
		pos.x += m_scorePosOffset;
	video->DrawBitmapText(pos, ss.str(), m_scoreFont, GS_BLACK);
}

void Pawn::Update(VideoPtr video, InputPtr input, EffectManagerPtr fxManager, const unsigned long lastFrameElapsedTimeMS)
{
	if (IsInArea(m_ball->m_pos, m_area, Vector2(0.0f, 0.0f)))
	{
		m_ball->m_currentArea = m_uniqueId;
	}

	m_controller->Update(this, video, input, fxManager, lastFrameElapsedTimeMS);
	DoBallBounce();
	LockInside();
}

int Pawn::GetScore() const
{
	return m_score;
}

void Pawn::AddToScore(const int score)
{
	m_score += score;
}

void Pawn::SetScore(const int score)
{
	m_score = score;
}

float Pawn::GetRadius() const
{
	return m_sprite->GetBitmapSizeF().x / 2.0f;
}

void Pawn::DoBallBounce()
{
	const float radiusSum = GetRadius()+m_ball->GetRadius();
	if (SquaredDistance(m_pos, m_ball->m_pos) <= (radiusSum*radiusSum))
	{
		const Vector2 wallDiff(m_ball->m_pos - m_pos);
		const Vector2 wallNormal = Normalize(wallDiff);
		const Vector2 reflect = ReflectVector(m_ball->m_dir, wallNormal);

		if (DP2(wallNormal, m_ball->m_dir) < 0)
		{
			m_ball->m_dir = reflect;
			m_ball->SetLastTouchOwnerId(m_uniqueId);
		}
	}
}

bool Pawn::GoalScored(VideoPtr video) const
{
	const float radiusSum = m_goal.GetRadius() + m_ball->GetRadius();
	if (SquaredDistance(m_goal.GetNormalizedPos()*video->GetScreenSizeF(), m_ball->GetPos()) < radiusSum*radiusSum)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Pawn::LockInside()
{
	Clamp(m_pos, GetRadius(), m_area);
}
