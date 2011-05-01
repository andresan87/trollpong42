#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include "StateManager.h"
#include "SpriteResourceManager.h"
#include "Controller.h"
#include "PawnManager.h"
#include "ZombieManager.h"
#include "TouchButton.h"

class GameState : public State
{
	std::vector<gs2d::str_type::string> m_bloodDecalNames;

	EffectManagerPtr m_fxManager;
	PawnManagerPtr m_pawnManager;
	ZombieManagerPtr m_zombieManager;
	BallPtr m_ball;
	TouchButton m_backButton;
	void DrawScenario(gs2d::VideoPtr video, SpriteResourceManager& spr);
	bool m_didOnce;

	boost::weak_ptr<GameState> weak_this;

    GameState& operator=(GameState const&);
	GameState();

public:
	static const gs2d::str_type::string GAME_STATE;

	static boost::shared_ptr<GameState> Create();
	void LoadResources(SpriteResourceManager &spr, gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio);
	void Update(SpriteResourceManager &spr, unsigned long lastFrameDeltaTimeMS, gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio);
	void Draw(SpriteResourceManager &spr, gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio);
};

#endif