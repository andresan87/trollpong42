#include "pong42.h" 
#include <sstream>

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
	m_barSprite = m_video->CreateSprite(GS_L("assets/textures/pong-bar.png"));
	m_backgroundSprite = m_video->CreateSprite(GS_L("assets/textures/background.png"));
	m_backgroundSprite->SetOrigin(Vector2(0.5f, 0.5f));

	m_dottedSprite = m_video->CreateSprite(GS_L("assets/textures/dotted.png"));
	m_dottedSprite->SetOrigin(Vector2(0.5f, 0.5f));
	m_barSprite->SetOrigin(Vector2(0.5f, 0.5f));
		
	for (int x = 0; x < 1; x++) {
		str_type::stringstream ss;
		ss << GS_L("assets/textures/") << x << GS_L(".png");
		SpritePtr sprite = m_video->CreateSprite(ss.str());
		sprite->SetOrigin(Vector2(0.5f, 0.5f));
		m_ballSprites.push_back(sprite);
	}
	
	m_ball = boost::shared_ptr<ball>(new ball(m_ballSprites[math::Randomizer::Int(m_ballSprites.size()-1)]));
	m_bar[0] = boost::shared_ptr<bar>(new bar(m_barSprite));
	m_bar[1] = boost::shared_ptr<bar>(new bar(m_barSprite));

}

Application::APP_STATUS Pong::Update(unsigned long lastFrameDeltaTimeMS)
{
	const Vector2 screenSize = m_video->GetScreenSizeF();
	const float padding = 20;
	const float initialVel = 5;
	if (m_ball->pos == Vector2(-1, -1)) {		
		m_ball->reset(screenSize, initialVel, m_ballSprites);
		
		m_bar[0]->pos = Vector2(padding, screenSize.y/2);
		m_bar[1]->pos = Vector2(screenSize.x - padding, screenSize.y/2);
	}

	Vector2 touch;

	if (m_ball->dir == Vector2(0,0)) {
		for (int t = 0; t <= 1; t++) {
			if (m_input->GetTouchState(t) == GSKS_HIT) {
				const Vector2 touchPos = m_input->GetTouchPos(t, m_video);
				m_ball->dir = Normalize(touchPos - m_ball->pos);
			}
		}
	}


	for (int t = 0; t <= 1; t++) {
		int player = -1;
		if ((touch = m_input->GetTouchPos(t, m_video)) != GS_NO_TOUCH) {
			if (touch.x < screenSize.x / 2) {
				player = 0;
			}
			else {
				player = 1;
			}
		}
		if (player != -1) {
			m_bar[player]->pos.y += m_input->GetTouchMove(t).y;
			if (m_bar[player]->pos.y <= 0) {
				m_bar[player]->pos.y = 0;
			}
			else if (m_bar[player]->pos.y >= screenSize.y) {
				m_bar[player]->pos.y = screenSize.y;
			}
		}
	}
	m_ball->angle += 1.0f;
	m_ball->pos += math::Normalize(m_ball->dir) * m_ball->vel;
	m_ball->wallCollide(screenSize);

	for (int t = 0; t <= 1; t++) {
		m_bar[t]->ballCollide(m_ball, screenSize, t, m_ballSprites);
	}


	return Application::APP_OK;
}

void Pong::RenderFrame()
{
	m_video->BeginSpriteScene(0xFFEAEAEA);
	m_backgroundSprite->Draw(m_video->GetScreenSizeF()/2, GS_COLOR(30, 0, 0 , 0), 0, Vector2(4, 4));
	m_dottedSprite->Stretch(Vector2(m_video->GetScreenSizeF().x/2, 0), Vector2(m_video->GetScreenSizeF().x/2, m_video->GetScreenSizeF().y), 10.0f, GS_BLACK, GS_BLACK);
	m_barSprite->Draw(m_bar[0]->pos);
	m_barSprite->Draw(m_bar[1]->pos);
	m_ball->draw();
	m_video->EndSpriteScene();
}

void Pong::Destroy()
{
}