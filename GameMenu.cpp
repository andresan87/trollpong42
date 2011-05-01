#include "GameMenu.h"
#include "GameState.h"

using namespace gs2d;
using namespace gs2d::math;

GameMenu::GameMenu() :
	m_resumeGame(Vector2(0, 0), Vector2(0.5f, 0.5f), GS_L("resume_game.png"), 0)
{
}

void GameMenu::LoadResources(SpriteResourceManager &spr, VideoPtr video, InputPtr input, AudioPtr audio)
{
	SpritePtr temp;
	temp = spr.GetSprite(video, GS_L("resume_game.png"));

	m_resumeGame.SetPos(video->GetScreenSizeF() * 0.5f);
}

void GameMenu::Update(SpriteResourceManager &spr, unsigned long lastFrameDeltaTimeMS, VideoPtr video, InputPtr input, AudioPtr audio)
{
	m_resumeGame.UpdateButton(video, input, spr);
	if (m_resumeGame.GetStatus() == TouchButton::ACTIVATED)
	{
		if (StateManager::GetIdleState(GameState::GAME_STATE))
		{
			StateManager::SetState(GameState::GAME_STATE);
		}
		else
		{
			StateManager::SetState(GameState::Create());
		}
		m_resumeGame.SetStatus(TouchButton::IDLE);
	}
}

void GameMenu::Draw(SpriteResourceManager &spr, VideoPtr video, InputPtr input, AudioPtr audio)
{
	video->BeginSpriteScene(GS_WHITE);
	m_resumeGame.DrawButton(video, input, spr);
	video->EndSpriteScene();
}

