#include "LoadScreen.h"
#include "GameState.h"

using namespace gs2d;
using namespace math;

ExistingState::ExistingState(const str_type::string& state) :
	m_state(state)
{
}

void ExistingState::SetState()
{
	StateManager::SetState(m_state);
}

NewState::NewState(StatePtr state) :
	m_state(state)
{
}

void NewState::SetState()
{
	StateManager::SetState(m_state);
}

LoadScreen::LoadScreen(AbstractStatePtr nextState, const str_type::string& text, const GS_COLOR color,
					   const str_type::string& font, const str_type::string& background) :
	m_nextState(nextState),
	m_text(text),
	m_font(font),
	m_background(background),
	m_color(color)
{
}

void LoadScreen::LoadResources(SpriteResourceManager &spr, VideoPtr video, InputPtr input, AudioPtr audio)
{
	spr.GetSprite(video, m_background);
	m_textSize = video->ComputeTextBoxSize(m_font, m_text);

	//m_shader = video->LoadShaderFromFile(GS_L("assets/shaders/default/default.vs"), GSSF_VERTEX);
}

void LoadScreen::Update(SpriteResourceManager &spr, unsigned long lastFrameDeltaTimeMS, VideoPtr video, InputPtr input, AudioPtr audio)
{
	m_nextState->SetState();
}

void LoadScreen::Draw(SpriteResourceManager &spr, VideoPtr video, InputPtr input, AudioPtr audio)
{
	video->BeginSpriteScene();
	//video->SetVertexShader(m_shader);
	spr.GetSprite(video, m_background)->DrawShaped(Vector2(0, 0), video->GetScreenSizeF(), GS_WHITE, GS_WHITE, GS_WHITE, GS_WHITE);
	// video->DrawBitmapText(Vector2(0, 0), m_text, m_font, m_color);
	// video->DrawBitmapText(Vector2(0, 0), GS_L("FILHADAPUTA"), GS_L("Verdana20_shadow.fnt"), m_color);
	//video->DrawBitmapText(video->GetScreenSizeF()/2.0f - m_textSize/2.0f, m_text, m_font, m_color);
	//video->SetVertexShader(ShaderPtr());
	//video->SetAlphaMode(GSAM_NONE);
	video->DrawBitmapText(video->GetScreenSizeF()/2.0f - m_textSize/2.0f, m_text, m_font, m_color);
	video->EndSpriteScene();
}
