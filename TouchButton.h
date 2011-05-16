#ifndef TOUCH_BUTTON_H_
#define TOUCH_BUTTON_H_

#include "Util.h"
#include "SpriteResourceManager.h"
#include "AudioResourceManager.h"

class TouchButton
{
public:
	enum STATUS
	{
		PRESSED = 0,
		SACTIVATED = 1,
		ACTIVATED,
		IDLE
	};

private:
	gs2d::math::Vector2 m_hitPos;
	gs2d::math::Vector2 m_lastTouch;
	STATUS m_status;
	gs2d::math::Vector2 m_pos, m_origin;
	unsigned int m_buttonFrame;
	gs2d::str_type::string m_buttonSprite;
	gs2d::str_type::string m_soundEffect;

public:
	TouchButton(gs2d::math::Vector2 pos, gs2d::math::Vector2 origin, gs2d::str_type::string buttonSprite,
				unsigned int buttonFrame, gs2d::str_type::string sound = GS_L(""));
	inline gs2d::math::Vector2 GetButtonSize(const gs2d::SpritePtr& sprite);
	void UpdateButton(gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio, SpriteResourceManager& spr, AudioResourceManager& aud);
	void DrawButton(gs2d::VideoPtr video, gs2d::InputPtr input, SpriteResourceManager& spr);
	STATUS GetStatus() const;
	void SetStatus(const STATUS status);
	gs2d::math::Vector2 GetPos() const;
	void SetPos(const gs2d::math::Vector2& pos);
};

typedef boost::shared_ptr<TouchButton> TouchButtonPtr;

#endif
