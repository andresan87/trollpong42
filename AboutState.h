#ifndef ABOUT_STATE_H_
#define ABOUT_STATE_H_

#include "StateManager.h"
#include "TouchButton.h"

class AboutState : public State
{
	TouchButton m_button;
public:
	AboutState();
	void LoadResources(SpriteResourceManager &spr, gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio);
	void Update(SpriteResourceManager &spr, unsigned long lastFrameDeltaTimeMS, gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio);
	void Draw(SpriteResourceManager &spr, gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio);
};


#endif