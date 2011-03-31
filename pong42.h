#include "../gs2d/src/gs2dframework.h"
#include <vector>

namespace gs2d {
class Pong : public BaseApplication
{
	VideoPtr m_video;
	InputPtr m_input;
	SpritePtr m_barSprite, m_backgroundSprite, m_dottedSprite;
	std::vector<SpritePtr> m_ballSprites;

	struct ball {
		math::Vector2 pos;
		float angle;
		float vel;
		math::Vector2 dir;
		SpritePtr sprite;
		float ballRadius;
		
		ball(SpritePtr spriteBall) {
			pos = math::Vector2(-1, -1);
			angle = 0;
			dir = math::Vector2(0, 0);
			vel = 0;
			sprite = spriteBall;
			ballRadius = sprite->GetBitmapSizeF().x / 2;
		}

		void wallCollide(const math::Vector2 &screenSize) {
			if (pos.y >= screenSize.y - ballRadius || pos.y <= ballRadius) {
				dir.y *= -1;				
			}
		}

		void reset(const math::Vector2 &screenSize, const float &initialVel, std::vector<SpritePtr> &m_ballSprites) {			
			pos = screenSize / 2;
			dir.y = 0;
			vel = initialVel;
			sprite = m_ballSprites[math::Randomizer::Int(m_ballSprites.size()-1)];
		}

		void draw() {
			sprite->Draw(pos, GS_WHITE, angle);
		}
	};

	struct bar {
		math::Vector2 pos;
		SpritePtr sprite;
		math::Vector2 size;

		bar(SpritePtr spriteBar) {
			pos = math::Vector2(-1, -1);
			size = spriteBar->GetBitmapSizeF();
		}

		void ballCollide(boost::shared_ptr<ball> m_ball, const math::Vector2 &screenSize, int bar, std::vector<SpritePtr> &ballSprites) {
			float leftBall = m_ball->pos.x - m_ball->ballRadius;
			float rightBall = m_ball->pos.x + m_ball->ballRadius;
			float bottomBall = m_ball->pos.y + m_ball->ballRadius;
			float topBall = m_ball->pos.y - m_ball->ballRadius;

			float topBar = pos.y - size.y/2;
			float bottomBar = pos.y + size.y/2;
	
			if ((bar == 1 && rightBall >= pos.x && m_ball->pos.x >= screenSize.x/2) ||
				(bar == 0 && leftBall <= pos.x && m_ball->pos.x < screenSize.x/2)) {
				if ((topBall >= topBar && topBall <= bottomBar) || (bottomBall >= topBar && bottomBall <= bottomBar)) {				
					m_ball->dir.x *= -1;
					m_ball->dir.y += (m_ball->pos.y - pos.y) / size.y;
					if (m_ball->vel <= 30) {
						m_ball->vel *= 1.1f;
					}
				}
				else {
					m_ball->reset(screenSize, 5, ballSprites);
				}
			}
		}
		
	};
	
	boost::shared_ptr<ball> m_ball;
	boost::shared_ptr<bar> m_bar[2];

	public:
		void Start(VideoPtr video, InputPtr input, AudioPtr audio);
		Application::APP_STATUS Update(unsigned long lastFrameDeltaTimeMS);
		void RenderFrame();
		void Destroy();
};
} //namespace gs2d