#ifndef GAME_ENTITY_H_
#define GAME_ENTITY_H_

#include "../gs2d/src/gs2dframework.h"
#include "EffectManager.h"

class GameEntity
{
protected:
	gs2d::math::Vector2 m_pos;

public:
	virtual void Draw(gs2d::VideoPtr video) = 0;
	virtual void Update(gs2d::VideoPtr video, gs2d::InputPtr input, EffectManagerPtr fxManager, const unsigned long lastFrameElapsedTimeMS) = 0;
	gs2d::math::Vector2 GetPos() const;
	void AddToPos(const gs2d::math::Vector2& v);
};

class Ball : public GameEntity
{
	friend class PlayerTouchController;
	friend class Pawn;

	gs2d::math::Vector2 m_dir;
	float m_angle, m_speed;
	int m_currentArea;
	gs2d::SpritePtr m_sprite, m_highlight, m_shadowSprite;

	int m_lastTouchOwnerId;

	void LockInside(gs2d::VideoPtr video);

	class TimeBomb
	{
		const unsigned long BOMB_TIME;
		const int NO_AREA;
		int m_area;
		unsigned long m_elapsedTime;

		void SetArea(const int area);

	public:
		TimeBomb();
		void Reset();
		void Update(const Ball* pBall, const unsigned long lastFrameElapsedTimeMS, const int area);
		bool MustExplode(const Ball* pBall) const;
		int GetArea() const;
		float GetExplosionBiasF() const;
		gs2d::GS_BYTE GetExplosionBias() const;
	} m_timeBomb;

public:
	Ball(gs2d::SpritePtr sprite, gs2d::SpritePtr highlight, gs2d::SpritePtr shadowSprite, gs2d::VideoPtr video);
	gs2d::math::Vector2 GetPos() const;
	gs2d::math::Vector2 GetDir() const;
	gs2d::SpritePtr GetSprite();
	bool MustExplode() const;
	void Reset(gs2d::VideoPtr video);
	float GetRadius() const;
	void SetLastTouchOwnerId(const int id);
	int GetTouchOwnerId() const;
	void Draw(gs2d::VideoPtr video);
	void Update(gs2d::VideoPtr video, gs2d::InputPtr input, EffectManagerPtr fxManager, const unsigned long lastFrameElapsedTimeMS);
	int GetCurrentArea() const;
};

typedef boost::shared_ptr<Ball> BallPtr;

class Controller;

class Pawn : public GameEntity
{
	class Goal
	{
		gs2d::SpritePtr m_sprite;
		gs2d::math::Vector2 m_normalizedPos;
	public:
		void Draw(gs2d::VideoPtr video) const;
		float GetRadius() const;
		gs2d::math::Vector2 GetNormalizedPos() const;
		Goal(gs2d::SpritePtr sprite, gs2d::math::Vector2 normalizedPos);
	} m_goal;

	friend class PlayerTouchController;

	gs2d::math::Rect2Df m_area;
	gs2d::SpritePtr m_sprite, m_shadowSprite;
	boost::shared_ptr<Controller> m_controller;
	BallPtr m_ball;
	int m_score;

	const gs2d::str_type::string m_scoreFont;
	const float m_scorePosOffset;

	void LockInside();
	void DoBallBounce();

public:
	Pawn(gs2d::SpritePtr sprite, const gs2d::math::Rect2Df &area,
		boost::shared_ptr<Controller> controller, BallPtr ball,
		const gs2d::math::Vector2& goalNormalizedPos, gs2d::SpritePtr goalSprite,
		const int uniqueId, gs2d::SpritePtr shadowSprite);
	float GetRadius() const;
	bool GoalScored(gs2d::VideoPtr video) const;
	int GetScore() const;
	void AddToScore(const int score);
	void SetScore(const int score);
	void Draw(gs2d::VideoPtr video);
	void DrawGoal(gs2d::VideoPtr video);
	void DrawScore(gs2d::VideoPtr video);
	void Update(gs2d::VideoPtr video, gs2d::InputPtr input, EffectManagerPtr fxManager, const unsigned long lastFrameElapsedTimeMS);
	const int m_uniqueId;
};

typedef boost::shared_ptr<Pawn> PawnPtr;

#endif