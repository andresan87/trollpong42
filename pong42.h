#include "../gs2d/src/gs2dframework.h"
#include "Controller.h"
#include "PawnManager.h"
#include "ZombieManager.h"

namespace gs2d {

class Pong : public BaseApplication
{
	VideoPtr m_video;
	InputPtr m_input;

	SpritePtr m_backgroundImage, m_lineSprite, m_pawnSprite,
		m_ballSprite, m_goalSprite, m_ballHighlight, m_bloodSprite;

	EffectManagerPtr m_fxManager;
	PawnManagerPtr m_pawnManager;
	ZombieManagerPtr m_zombieManager;
	BallPtr m_ball;
	void DrawScenario();

public:
	void Start(VideoPtr video, InputPtr input, AudioPtr audio);
	Application::APP_STATUS Update(unsigned long lastFrameDeltaTimeMS);
	void RenderFrame();
	void Destroy();
};

} //namespace gs2d