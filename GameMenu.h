#ifndef GAME_MENU_H_
#define GAME_MENU_H_

#include "StateManager.h"
#include "SpriteResourceManager.h"
#include "TouchButton.h"

class GameMenu : public State
{
	TouchButton m_resumeGame;

public:
	GameMenu();
	void LoadResources(SpriteResourceManager &spr, gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio);
	void Update(SpriteResourceManager &spr, unsigned long lastFrameDeltaTimeMS, gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio);
	void Draw(SpriteResourceManager &spr, gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio);
};


#endif