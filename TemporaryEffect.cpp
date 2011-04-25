#include "TemporaryEffect.h"
#include "Util.h"

using namespace gs2d;
using namespace gs2d::math;

SingleParticle::SingleParticle(VideoPtr video, const str_type::string& sprite, const Vector2& pos, const float spinSpeed,
				   const unsigned long duration, const float growth, const gs2d::math::Vector2& size,
				   const float alphaCap, const bool invertAlpha, const bool fadeOut, const float angle,
				   const bool modulate) :
	m_sprite(sprite),
	m_pos(pos),
	m_spinSpeed(spinSpeed),
	m_duration(duration),
	m_elapsedTime(0),
	m_angle(angle),
	m_growth(growth),
	m_scale(1.0f),
	m_size(size),
	m_alphaCap(alphaCap),
	m_invertAlpha(invertAlpha),
	m_startTime(video->GetElapsedTime()),
	m_fadeOut(fadeOut),
	m_modulate(modulate)
{
}

bool SingleParticle::IsOver() const
{
	if (m_elapsedTime > m_duration)
		return true;
	else
		return false;
}

void SingleParticle::Draw(gs2d::VideoPtr video, SpriteResourceManager& spr)
{
	float fade;

	SpritePtr sprite = spr.GetSprite(video, m_sprite);

	if (m_fadeOut)
		fade = Max(0.0f, Min(1.0f, (static_cast<float>(m_elapsedTime) / static_cast<float>(m_duration))));
	else
		fade = 0.0f;

	if (!m_invertAlpha)
		fade = 1.0f - fade;

	const GS_COLOR color = GS_COLOR(static_cast<GS_BYTE>(fade * 255.0f * m_alphaCap), 255, 255, 255);

	const int numRects = sprite->GetNumRects();
	if (numRects > 1)
	{
		float frame = Max(0.0f, Min(1.0f, (static_cast<float>(m_elapsedTime) / static_cast<float>(m_duration)))) * static_cast<float>(numRects-1);
		sprite->SetRect(static_cast<unsigned int>(frame));
	}

	if (m_modulate)
	{
		video->SetAlphaMode(GSAM_MODULATE);
	}
	sprite->DrawShaped(m_pos, m_size * m_scale, color, color, color, color, m_angle);
	if (m_modulate)
	{
		video->SetAlphaMode(GSAM_PIXEL);
	}
}

void SingleParticle::Update(gs2d::VideoPtr video, const unsigned long elapsedTime, SpriteResourceManager& spr)
{
	m_elapsedTime = video->GetElapsedTime() - m_startTime;
	m_angle += m_spinSpeed / AssertFPS(video);
	m_scale += m_growth / AssertFPS(video);
}
