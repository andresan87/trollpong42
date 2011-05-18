#include "TouchButton.h"

using namespace gs2d;
using namespace gs2d::math;

TouchButton::TouchButton(Vector2 pos, Vector2 origin, gs2d::str_type::string buttonSprite,
						 unsigned int buttonFrame, gs2d::str_type::string sound) :
	m_status(IDLE),
	m_hitPos(-30, -30),
	m_soundEffect(sound),
	m_buttonFrame(buttonFrame),
	m_buttonSprite(buttonSprite),
	m_pos(pos),
	m_origin(origin)
{
}

inline Vector2 TouchButton::GetButtonSize(const SpritePtr& sprite)
{
	Vector2 frameSize(sprite->GetBitmapSizeF());
	if (sprite->GetRect().size != Vector2(0, 0))
	{
		frameSize = sprite->GetRect().size;
	}
	return frameSize;
}

void TouchButton::UpdateButton(VideoPtr video, InputPtr input, AudioPtr audio, SpriteResourceManager& spr, AudioResourceManager& aud)
{
	SpritePtr sprite = spr.GetSprite(video, m_buttonSprite);
	const Vector2 frameSize(GetButtonSize(sprite));
	const Vector2 currentTouch(input->GetTouchPos(0, video));
	if (input->GetTouchState(0) == GSKS_HIT && currentTouch != GS_NO_TOUCH)
		m_hitPos = currentTouch;

	if (m_status == SACTIVATED)
	{
		m_status = ACTIVATED;
	}

	if (currentTouch != GS_NO_TOUCH)
	{
		m_lastTouch = currentTouch;
		if (IsInArea(currentTouch, Rect2Df(m_pos, frameSize), m_origin) && IsInArea(m_hitPos, Rect2Df(m_pos, frameSize), m_origin))
		{
			m_status = PRESSED;
		}
		else
		{
			m_status = IDLE;
		}
	}

	if (input->GetTouchState(0) == GSKS_RELEASE)
	{
		if (IsInArea(m_lastTouch, Rect2Df(m_pos, frameSize), m_origin) && IsInArea(m_hitPos, Rect2Df(m_pos, frameSize), m_origin))
		{
			m_status = SACTIVATED;
			if (m_soundEffect != GS_L(""))
			{
				aud.GetSample(audio, m_soundEffect)->Play();
			}
		}
	}
}

void TouchButton::DrawButton(VideoPtr video, InputPtr input, SpriteResourceManager& spr)
{
	SpritePtr sprite = spr.GetSprite(video, m_buttonSprite);
	video->SetAlphaMode(GSAM_PIXEL);
	if (sprite)
	{
		sprite->SetRect(m_buttonFrame);
		sprite->SetOrigin(m_origin);
		sprite->Draw(m_pos);

		if (m_status == PRESSED)
		{
			video->SetAlphaMode(GSAM_ADD);
			sprite->Draw(m_pos);
			video->SetAlphaMode(GSAM_PIXEL);
		}
	}
}

TouchButton::STATUS TouchButton::GetStatus() const
{
	return m_status;
}

void TouchButton::SetStatus(const TouchButton::STATUS status)
{
	m_status = status;
}

Vector2 TouchButton::GetPos() const
{
	return m_pos;
}

void TouchButton::SetPos(const Vector2& pos)
{
	m_pos = pos;
}
