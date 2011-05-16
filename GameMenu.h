#ifndef GAME_MENU_H_
#define GAME_MENU_H_

#include "StateManager.h"
#include "SpriteResourceManager.h"
#include "TouchButton.h"

class GameMenu : public State
{
	std::vector<TouchButtonPtr> m_buttons;

	enum BUTTON
	{
		NEW_GAME = 0,
		RESUME_GAME = 1,
		ABOUT = 2,
		EXIT = 3
	};

public:
	GameMenu();
	void LoadResources(SpriteResourceManager &spr, gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio);
	void Update(SpriteResourceManager &spr, unsigned long lastFrameDeltaTimeMS, gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio);
	void Draw(SpriteResourceManager &spr, gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio);
};


#endif