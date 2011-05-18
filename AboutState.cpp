#include "AboutState.h"
#include "GameMenu.h"

using namespace gs2d;
using namespace gs2d::math;

AboutState::AboutState() :
	m_button(Vector2(0,0), Vector2(0.5f, 1.0f), GS_L("resume.png"), 0)
{
}

void AboutState::LoadResources(SpriteResourceManager &spr, VideoPtr video, InputPtr input, AudioPtr audio)
{
	spr.GetSprite(video, GS_L("resume.png"));
	SpritePtr temp = spr.GetSprite(video, GS_L("ice.jpg"));
	temp->SetOrigin(Vector2(0, 0));
}

void AboutState::Update(SpriteResourceManager &spr, unsigned long lastFrameDeltaTimeMS, VideoPtr video, InputPtr input, AudioPtr audio)
{
	m_button.SetPos(video->GetScreenSizeF() * Vector2(0.5f, 1.0f));
	m_button.UpdateButton(video, input, audio, spr, StateManager::m_aud);
	if (m_button.GetStatus() == TouchButton::ACTIVATED)
	{
		StateManager::SetState(StatePtr(new GameMenu));
		m_button.SetStatus(TouchButton::IDLE);
	}
}

void AboutState::Draw(SpriteResourceManager &spr, VideoPtr video, InputPtr input, AudioPtr audio)
{
	video->BeginSpriteScene();
	spr.GetSprite(video, GS_L("ice.jpg"))->DrawShaped(Vector2(0, 0), video->GetScreenSizeF(), GS_WHITE, GS_WHITE, GS_WHITE, GS_WHITE);
	m_button.DrawButton(video, input, spr);
	video->DrawBitmapText(Vector2(100, 100), 
		GS_L("Zombicide Hockey - ALPHA version\n\n") \
		GS_L("This is a \'space hockey\' style game made for two players\n\n") \
		GS_L("We recommended you to play it on a tablet.\n\n") \
		GS_L("Click the screen to move you pawn (sliding doesn't help it :).\n\n") \
		GS_L("You can score points by hitting the oponent\'s goal or by killing zombies\n\n") \
		GS_L("Next versions will include single player mode."),
		GS_L("Verdana20_shadow.fnt"), GS_BLACK);
	DrawFPSRate(video);
	video->EndSpriteScene();
}
