#ifndef GAME_ENTITY_H_
#define GAME_ENTITY_H_

#include "../gs2d/src/gs2dframework.h"
#include "EffectManager.h"
#include "SpriteResourceManager.h"

class GameEntity
{
protected:
	gs2d::math::Vector2 m_pos;

public:
	virtual void Draw(gs2d::VideoPtr video, SpriteResourceManager& spr) = 0;
	virtual void Update(gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio, EffectManagerPtr fxManager,
		const unsigned long lastFrameElapsedTimeMS, SpriteResourceManager& spr) = 0;
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
	gs2d::str_type::string m_sprite, m_highlight, m_shadowSprite;

	int m_lastTouchOwnerId;

	void LockInside(gs2d::VideoPtr video, gs2d::AudioPtr audio, SpriteResourceManager& spr);

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
	Ball(gs2d::VideoPtr video);
	gs2d::math::Vector2 GetPos() const;
	gs2d::math::Vector2 GetDir() const;
	gs2d::str_type::string GetSpriteName();
	bool MustExplode() const;
	void Reset(gs2d::VideoPtr video);
	float GetRadius(SpriteResourceManager& spr, gs2d::VideoPtr video) const;
	void SetLastTouchOwnerId(const int id);
	int GetTouchOwnerId() const;
	void Draw(gs2d::VideoPtr video, SpriteResourceManager& spr);
	void Update(gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio, EffectManagerPtr fxManager,
		const unsigned long lastFrameElapsedTimeMS, SpriteResourceManager& spr);
	int GetCurrentArea() const;
};

typedef boost::shared_ptr<Ball> BallPtr;

class Controller;

class Pawn : public GameEntity
{
	class Goal
	{
		gs2d::str_type::string m_sprite;
		gs2d::math::Vector2 m_normalizedPos;
	public:
		void Draw(gs2d::VideoPtr video, SpriteResourceManager& spr) const;
		float GetRadius(SpriteResourceManager& spr, gs2d::VideoPtr video) const;
		gs2d::math::Vector2 GetNormalizedPos() const;
		Goal(gs2d::math::Vector2 normalizedPos);
	} m_goal;

	friend class PlayerTouchController;

	gs2d::math::Rect2Df m_area;
	gs2d::str_type::string m_sprite, m_shadowSprite;
	boost::shared_ptr<Controller> m_controller;
	BallPtr m_ball;
	int m_score;

	const gs2d::str_type::string m_scoreFont;
	const float m_scorePosOffset;

	void LockInside(SpriteResourceManager& spr, gs2d::VideoPtr video);
	void DoBallBounce(SpriteResourceManager& spr, gs2d::VideoPtr video, gs2d::AudioPtr audio);

public:
	Pawn(const gs2d::math::Rect2Df &area,
		boost::shared_ptr<Controller> controller, BallPtr ball,
		const gs2d::math::Vector2& goalNormalizedPos,
		const int uniqueId);
	float GetRadius(SpriteResourceManager& spr, gs2d::VideoPtr video) const;
	bool GoalScored(gs2d::VideoPtr video, SpriteResourceManager& spr) const;
	int GetScore() const;
	void AddToScore(const int score);
	void SetScore(const int score);
	void Draw(gs2d::VideoPtr video, SpriteResourceManager& spr);
	void DrawGoal(gs2d::VideoPtr video, SpriteResourceManager& spr);
	void DrawScore(gs2d::VideoPtr video);
	void Update(gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio, EffectManagerPtr fxManager,
		const unsigned long lastFrameElapsedTimeMS, SpriteResourceManager& spr);
	const int m_uniqueId;
};

typedef boost::shared_ptr<Pawn> PawnPtr;

#endif