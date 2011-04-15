#include "pong42.h" 
#include <sstream>
#include "Util.h"

using namespace gs2d;
using namespace gs2d::math;

gs2d::BaseApplicationPtr gs2d::CreateBaseApplication()
{
	return BaseApplicationPtr(new Pong);
}

void Pong::Start(VideoPtr video, InputPtr input, AudioPtr audio)
{
	m_video = video;
	m_input = input;

	m_backgroundImage = video->CreateSprite(GS_L("assets/textures/background.png"));
	m_backgroundImage->SetOrigin(Vector2(0.5f, 0.5f));

	m_lineSprite = video->CreateSprite(GS_L("assets/textures/dotted.png"));

	m_pawnSprite = video->CreateSprite(GS_L("assets/textures/pawn.png"));
	m_pawnSprite->SetOrigin(GSEO_CENTER);

	m_ballSprite = video->CreateSprite(GS_L("assets/textures/ball.png"));
	m_ballSprite->SetOrigin(GSEO_CENTER);

	m_ballHighlight = video->CreateSprite(GS_L("assets/textures/ball_highlight.png"));
	m_ballHighlight->SetOrigin(GSEO_CENTER);

	m_goalSprite = video->CreateSprite(GS_L("assets/textures/goal.png"));
	m_goalSprite->SetOrigin(GSEO_CENTER_BOTTOM);

	m_bloodSprite = video->CreateSprite(GS_L("assets/textures/blood01.png"));
	m_bloodSprite->SetOrigin(GSEO_CENTER);
	m_bloodSprite->SetupSpriteRects(6, 1);

	m_ball = BallPtr(new Ball(m_ballSprite, m_ballHighlight, video));
	m_pawnManager = PawnManagerPtr(new PawnManager(video, m_pawnSprite, m_pawnSprite, m_goalSprite, m_ball));

	m_fxManager = EffectManagerPtr(new EffectManager());

	std::vector<SpritePtr> sprites;
	sprites.push_back(video->CreateSprite(GS_L("assets/textures/zombies/zombie01.png")));
	sprites.push_back(video->CreateSprite(GS_L("assets/textures/zombies/zombie02.png")));
	sprites.push_back(video->CreateSprite(GS_L("assets/textures/zombies/zombie03.png")));
	sprites.push_back(video->CreateSprite(GS_L("assets/textures/zombies/zombie04.png")));
	m_zombieManager = ZombieManagerPtr(new ZombieManager(video, sprites, m_ball, m_bloodSprite));
}

Application::APP_STATUS Pong::Update(unsigned long lastFrameDeltaTimeMS)
{
	m_fxManager->Update(m_video, lastFrameDeltaTimeMS);
	m_pawnManager->Update(m_video, m_input, m_fxManager);
	m_ball->Update(m_video, m_input, m_fxManager);
	m_zombieManager->Update(m_video, m_input, lastFrameDeltaTimeMS, m_fxManager);
	return Application::APP_OK;
}

void Pong::RenderFrame()
{
	m_video->BeginSpriteScene(0xFFEAEAEA);
	DrawScenario();
	m_fxManager->Draw(m_video);
	m_pawnManager->Draw(m_video);
	m_ball->Draw(m_video);

	str_type::stringstream ss;
	ss << m_video->GetFPSRate();
	m_video->DrawBitmapText(Vector2(0,0), ss.str(), GS_L("Verdana20_shadow.fnt"), GS_COLOR(20,0,0,0));

	m_zombieManager->Draw(m_video);
	m_video->EndSpriteScene();
}

void Pong::DrawScenario()
{
	const Vector2 screenSize = m_video->GetScreenSizeF();
	const Vector2 halfScreenSize = screenSize/2.0f;

	m_backgroundImage->Draw(halfScreenSize, GS_COLOR(30, 0, 0, 0), 0, Vector2(2, 2));

	const GS_COLOR lineColor = GS_COLOR(40,0,0,0);
	m_lineSprite->Stretch(Vector2(halfScreenSize.x, 0), Vector2(halfScreenSize.x, screenSize.y), 22, lineColor, lineColor);
}

void Pong::Destroy()
{
}
