#include "GameMenu.h"
#include "GameState.h"
#include "LoadScreen.h"
#include "AboutState.h"

using namespace gs2d;
using namespace gs2d::math;

GameMenu::GameMenu() :
	m_buttons(4)
{
	for (std::size_t t=0; t<m_buttons.size(); t++)
	{
		m_buttons[t] = TouchButtonPtr(new TouchButton(Vector2(0, 0), Vector2(0.5f, 0.5f), GS_L("menu_buttons.png"), t, GS_L("score.ogg")));
	}
}

void GameMenu::LoadResources(SpriteResourceManager &spr, VideoPtr video, InputPtr input, AudioPtr audio)
{
	static const float BUTTON_STRIDE = 64.0f;
	for (std::size_t t=0; t<m_buttons.size(); t++)
	{
		m_buttons[t]->SetPos(video->GetScreenSizeF() * 0.5f + Vector2(0.0f, (static_cast<float>(t) * BUTTON_STRIDE)));
	}

	SpritePtr temp;
	temp = spr.GetSprite(video, GS_L("menu_buttons.png"), 1, 4);
	temp->SetOrigin(GSEO_CENTER);
	temp = spr.GetSprite(video, GS_L("title.png"));
	temp->SetOrigin(GSEO_CENTER);
	temp = spr.GetSprite(video, GS_L("jeralogo.png"));
	temp->SetOrigin(Vector2(1.0f, 1.0f));

	spr.GetSprite(video, GS_L("ice.jpg"));
	spr.GetSprite(video, GS_L("jeralogo.png"));

	StateManager::m_aud.GetSample(audio, GS_L("score.ogg"));
}

void GameMenu::Update(SpriteResourceManager &spr, unsigned long lastFrameDeltaTimeMS, VideoPtr video, InputPtr input, AudioPtr audio)
{
	for (std::size_t t=0; t<m_buttons.size(); t++)
	{
		m_buttons[t]->UpdateButton(video, input, audio, spr, StateManager::m_aud);
		if (m_buttons[t]->GetStatus() == TouchButton::ACTIVATED)
		{
			AbstractStatePtr state;
			switch (t)
			{
			case NEW_GAME:
				// StateManager::SetState(GameState::Create());
				state = AbstractStatePtr(new NewState(GameState::Create()));
				StateManager::SetState(StatePtr(new LoadScreen(state, GS_L("Loading..."), GS_BLACK, GS_L("Arcade80.fnt"), GS_L("ice.jpg"))));
				break;

			case RESUME_GAME:
				if (StateManager::GetIdleState(GameState::GAME_STATE))
				{
					// StateManager::SetState(GameState::GAME_STATE);
					state = AbstractStatePtr(new ExistingState(GameState::GAME_STATE));
					StateManager::SetState(StatePtr(new LoadScreen(state, GS_L("Loading..."), GS_BLACK, GS_L("Arcade80.fnt"), GS_L("ice.jpg"))));
				}
				else
				{
					// StateManager::SetState(GameState::Create());
					state = NewStatePtr(new NewState(GameState::Create()));
					StateManager::SetState(StatePtr(new LoadScreen(state, GS_L("Loading..."), GS_BLACK, GS_L("Arcade80.fnt"), GS_L("ice.jpg"))));
				}
				break;

			case ABOUT:
				StateManager::SetState(StatePtr(new AboutState));
				break;

			case EXIT:
				video->Quit();
				break;
			};
			m_buttons[t]->SetStatus(TouchButton::IDLE);
		}
	}
}

void GameMenu::Draw(SpriteResourceManager &spr, VideoPtr video, InputPtr input, AudioPtr audio)
{
	video->BeginSpriteScene(GS_WHITE);
	//video->DrawBitmapText(Vector2(0,0), GS_L("Seila"), GS_L("Verdana20_shadow.fnt"), GS_WHITE);
	spr.GetSprite(video, GS_L("ice.jpg"))->DrawShaped(Vector2(0, 0), video->GetScreenSizeF(), GS_WHITE, GS_WHITE, GS_WHITE, GS_WHITE);

	SpritePtr title = spr.GetSprite(video, GS_L("title.png" ));
	title->Draw(Vector2(video->GetScreenSizeF().x/2.0f, (video->GetScreenSizeF().y/2.0f) - title->GetBitmapSizeF().y), GS_WHITE, 5.0f);

	for (std::size_t t=0; t<m_buttons.size(); t++)
	{
		m_buttons[t]->DrawButton(video, input, spr);
	}

	spr.GetSprite(video, GS_L("jeralogo.png"))->Draw(video->GetScreenSizeF(), GS_COLOR(192, 0, 0, 0));
	DrawFPSRate(video);
	video->EndSpriteScene();
}
