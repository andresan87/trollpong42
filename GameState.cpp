#include "GameState.h"

using namespace gs2d;
using namespace gs2d::math;

GameState::GameState() :
	m_bloodDecalNames(2)
{
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

	m_ball = BallPtr(new Ball(video));
	m_pawnManager = PawnManagerPtr(new PawnManager(video, m_ball));

	m_fxManager = EffectManagerPtr(new EffectManager());

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
	m_zombieManager = ZombieManagerPtr(new ZombieManager(video, sprites, m_ball, m_bloodDecalNames));
}

void GameState::Update(SpriteResourceManager& spr, unsigned long lastFrameDeltaTimeMS, VideoPtr video, InputPtr input, AudioPtr audio)
{
	m_fxManager->Update(video, lastFrameDeltaTimeMS, spr);
	m_pawnManager->Update(video, input, m_fxManager, lastFrameDeltaTimeMS, spr);
	m_ball->Update(video, input, m_fxManager, lastFrameDeltaTimeMS, spr);
	m_zombieManager->Update(spr, video, input, lastFrameDeltaTimeMS, m_fxManager, m_pawnManager);
}

void GameState::Draw(SpriteResourceManager &spr, VideoPtr video, InputPtr input, AudioPtr audio)
{
	video->BeginSpriteScene(0xFFEAEAEA);
	DrawScenario(video, spr);
	m_pawnManager->Draw(video, spr);
	m_ball->Draw(video, spr);

	m_zombieManager->Draw(video, spr);

	m_fxManager->DrawMain(video, spr);

	str_type::stringstream ss;
	ss << video->GetFPSRate();
	video->DrawBitmapText(Vector2(0,0), ss.str(), GS_L("Verdana20_shadow.fnt"), GS_COLOR(40,255,255,255));
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
