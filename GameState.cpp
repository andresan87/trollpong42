#include "GameState.h"
#include "GameMenu.h"

using namespace gs2d;
using namespace gs2d::math;

const str_type::string GameState::GAME_STATE = GS_L("game");

GameState::GameState() :
	m_bloodDecalNames(2),
	m_backButton(Vector2(100, 100), Vector2(0.5f, 1.0f), GS_L("back.png"), 0),
	m_didOnce(false)
{
}

boost::shared_ptr<GameState> GameState::Create()
{
	boost::shared_ptr<GameState> pi(new GameState);
	pi->weak_this = pi;
	return pi;
}

GameState& GameState::operator=(GameState const& other)
{
	return *this; // can't copy raw type
}

void GameState::LoadResources(SpriteResourceManager &spr, VideoPtr video, InputPtr input, AudioPtr audio)
{
	SpritePtr temp;
	temp = spr.GetSprite(video, GS_L("ice.jpg"));
	temp->SetOrigin(Vector2(0.0f, 0.0f));

	temp = spr.GetSprite(video, GS_L("dotted.png"));

	temp = spr.GetSprite(video, GS_L("pawn.png"));
	temp->SetOrigin(GSEO_CENTER);

	temp = spr.GetSprite(video, GS_L("ball.png"));
	temp->SetOrigin(GSEO_CENTER);

	temp = spr.GetSprite(video, GS_L("ball_highlight.png"));
	temp->SetOrigin(GSEO_CENTER);

	temp = spr.GetSprite(video, GS_L("back.png"));

	temp = spr.GetSprite(video, GS_L("goal.png"));
	temp->SetOrigin(GSEO_CENTER_BOTTOM);

	temp = spr.GetSprite(video, GS_L("shadow.png"));
	temp->SetOrigin(GSEO_CENTER);

	temp = spr.GetSprite(video, GS_L("char_shadow.png"));
	temp->SetOrigin(GSEO_CENTER);

	temp = spr.GetSprite(video, GS_L("blood01.png"), 6, 1);
	temp->SetOrigin(GSEO_CENTER);

	temp = spr.GetSprite(video, GS_L("explosion.png"));
	temp->SetOrigin(GSEO_CENTER);
	temp->SetupSpriteRects(5, 5);

	m_bloodDecalNames.clear();
	m_bloodDecalNames.push_back(GS_L("blood_stain01.png"));
	m_bloodDecalNames.push_back(GS_L("blood_stain02.png"));

	for (std::size_t t = 0; t < m_bloodDecalNames.size(); t++)
	{
		SpritePtr bloodDecal = spr.GetSprite(video, m_bloodDecalNames[t]);
		bloodDecal->SetOrigin(GSEO_CENTER);
	}

	std::vector<str_type::string> sprites;
	sprites.push_back(GS_L("zombies/zombie01.png"));
	sprites.push_back(GS_L("zombies/zombie02.png"));
	sprites.push_back(GS_L("zombies/zombie03.png"));
	sprites.push_back(GS_L("zombies/zombie04.png"));

	for (std::size_t t = 0; t < sprites.size(); t++)
	{
		SpritePtr sprite = spr.GetSprite(video, sprites[t]);
		sprite->SetupSpriteRects(4, 4);
		sprite->SetOrigin(GSEO_CENTER_BOTTOM);
	}

	if (!m_didOnce)
	{
		m_ball = BallPtr(new Ball(video));
		m_pawnManager = PawnManagerPtr(new PawnManager(video, m_ball));
		m_fxManager = EffectManagerPtr(new EffectManager());
		m_zombieManager = ZombieManagerPtr(new ZombieManager(video, sprites, m_ball, m_bloodDecalNames));
		m_didOnce = true;
	}

	m_backButton.SetPos(video->GetScreenSizeF() * Vector2(0.5f, 1.0f));
	m_zombieManager->FillSpritePtrs(video, spr);

	//StateManager::m_aud.ReleaseAll();
	StateManager::m_aud.GetSample(audio, GS_L("pawnhit.mp3"));
	StateManager::m_aud.GetSample(audio, GS_L("sidehit.mp3"));
	StateManager::m_aud.GetSample(audio, GS_L("zombiedeath.ogg"));
	StateManager::m_aud.GetSample(audio, GS_L("score.ogg"));
	StateManager::m_aud.GetSample(audio, GS_L("explosion.ogg"));
}

void GameState::Update(SpriteResourceManager& spr, unsigned long lastFrameDeltaTimeMS, VideoPtr video, InputPtr input, AudioPtr audio)
{
	m_fxManager->Update(video, lastFrameDeltaTimeMS, spr);
	m_pawnManager->Update(video, input, audio, m_fxManager, lastFrameDeltaTimeMS, spr);
	m_ball->Update(video, input, audio, m_fxManager, lastFrameDeltaTimeMS, spr);
	m_zombieManager->Update(spr, video, input, audio, lastFrameDeltaTimeMS, m_fxManager, m_pawnManager);
	m_backButton.UpdateButton(video, input, spr);

	if (m_backButton.GetStatus() == TouchButton::ACTIVATED)
	{
		StateManager::PushIdleState(GameState::GAME_STATE, boost::shared_ptr<State>(weak_this));
		StateManager::SetState(StatePtr(new GameMenu()));
		m_backButton.SetStatus(TouchButton::IDLE);
	}
}

void GameState::Draw(SpriteResourceManager &spr, VideoPtr video, InputPtr input, AudioPtr audio)
{
	video->BeginSpriteScene(0xFFEAEAEA);
	video->UnsetScissor();
	DrawScenario(video, spr);
	m_pawnManager->Draw(video, spr);
	m_ball->Draw(video, spr);

	m_zombieManager->Draw(video, spr);

	m_fxManager->DrawMain(video, spr);

	str_type::stringstream ss;
	ss << video->GetFPSRate();
	video->DrawBitmapText(Vector2(0,0), ss.str(), GS_L("Verdana20_shadow.fnt"), GS_COLOR(40,255,255,255));

	m_backButton.DrawButton(video, input, spr);
	video->EndSpriteScene();
}

void GameState::DrawScenario(VideoPtr video, SpriteResourceManager& spr)
{
	const Vector2 screenSize = video->GetScreenSizeF();
	const Vector2 halfScreenSize = screenSize/2.0f;

	spr.GetSprite(video, GS_L("ice.jpg"))->DrawShaped(Vector2(0, 0), screenSize, GS_WHITE, GS_WHITE, GS_WHITE, GS_WHITE);
	m_fxManager->DrawGround(video, spr);

	const GS_COLOR lineColor = GS_COLOR(40,0,0,0);
	spr.GetSprite(video, GS_L("dotted.png"))->Stretch(Vector2(halfScreenSize.x, 0), Vector2(halfScreenSize.x, screenSize.y), 22, lineColor, lineColor);
}
