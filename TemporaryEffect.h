#ifndef TEMPORARY_EFFECT_H_
#define TEMPORARY_EFFECT_H_

#include "../gs2d/src/gs2dframework.h"
#include "SpriteResourceManager.h"

class TemporaryEffect
{
public:
	virtual bool IsOver() const = 0;
	virtual void Draw(gs2d::VideoPtr video, SpriteResourceManager& spr) = 0;
	virtual void Update(gs2d::VideoPtr video, const unsigned long elapsedTime, SpriteResourceManager& spr) = 0;
};

typedef boost::shared_ptr<TemporaryEffect> TemporaryEffectPtr;

class SingleParticle : public TemporaryEffect
{
	gs2d::math::Vector2 m_pos;
	const gs2d::math::Vector2 m_size;
	float m_angle;
	const bool m_invertAlpha;
	const float m_alphaCap;
	const float m_spinSpeed;
	const bool m_fadeOut;
	const bool m_modulate;
	float m_growth, m_scale;
	gs2d::str_type::string m_sprite;
	const unsigned long m_duration;
	unsigned long m_elapsedTime;
	const unsigned long m_startTime;
public:
	SingleParticle(gs2d::VideoPtr video, const gs2d::str_type::string& sprite, const gs2d::math::Vector2& pos, const float spinSpeed,
		const unsigned long duration, const float growth, const gs2d::math::Vector2& size, const float alphaCap,
		const bool invertAlpha, const bool fadeOut = true, const float angle = 0.0f, const bool modulate = false);
	bool IsOver() const;
	void Draw(gs2d::VideoPtr video, SpriteResourceManager& spr);
	void Update(gs2d::VideoPtr video, const unsigned long elapsedTime, SpriteResourceManager& spr);
};

typedef boost::shared_ptr<SingleParticle> SingleParticlePtr;

#endif