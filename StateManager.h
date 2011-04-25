#ifndef STATE_MANAGER_H_
#define STATE_MANAGER_H_

#include "../gs2d/src/gs2dframework.h"
#include "SpriteResourceManager.h"
#include <map>

class State
{
public:
	virtual void LoadResources(SpriteResourceManager &spr, gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio) = 0;
	virtual void Update(SpriteResourceManager &spr, unsigned long lastFrameDeltaTimeMS, gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio) = 0;
	virtual void Draw(SpriteResourceManager &spr, gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio) = 0;
	// virtual void ReleaseResources() = 0;
};

typedef boost::shared_ptr<State> StatePtr;

class StateManager : public gs2d::BaseApplication
{
	gs2d::VideoPtr m_video;
	gs2d::AudioPtr m_audio;
	gs2d::InputPtr m_input;

	SpriteResourceManager m_spr;
	StatePtr m_currentState;

	static StatePtr m_nextState;
	static std::map<gs2d::str_type::string, StatePtr> m_idleStates;

	void Start(gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio);
	gs2d::Application::APP_STATUS Update(unsigned long lastFrameDeltaTimeMS);
	void RenderFrame();
	void Destroy();

	void SwapState();

public:
	StateManager(const StatePtr& state);

	void PushIdleState(const gs2d::str_type::string& name, const StatePtr& state);
	static void SetState(const gs2d::str_type::string& name);
	static void SetState(const StatePtr& state);
	StatePtr GetCurrentState();
};

typedef boost::shared_ptr<StateManager> StateManagerPtr;

#endif
