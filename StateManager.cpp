#include "StateManager.h"

using namespace gs2d;
using namespace gs2d::math;

StatePtr StateManager::m_nextState;
std::map<str_type::string, StatePtr> StateManager::m_idleStates;

StateManager::StateManager(const StatePtr& state)
{
	m_currentState = state;
}

void StateManager::Start(VideoPtr video, InputPtr input, AudioPtr audio)
{
	m_video = video;
	m_input = input;
	m_audio = audio;
	m_currentState->LoadResources(m_spr, m_video, m_input, m_audio);
}

void StateManager::SwapState()
{
	if (m_nextState)
	{
		m_currentState = m_nextState;
		m_currentState->LoadResources(m_spr, m_video, m_input, m_audio);
		m_nextState.reset();
	}
}

Application::APP_STATUS StateManager::Update(unsigned long lastFrameDeltaTimeMS)
{
	SwapState();
	m_currentState->Update(m_spr, lastFrameDeltaTimeMS, m_video, m_input, m_audio);
	return Application::APP_OK;
}

void StateManager::RenderFrame()
{
	m_currentState->Draw(m_spr, m_video, m_input, m_audio);
}

void StateManager::Destroy()
{
	m_spr.ReleaseAll();
	// unload audio resource manager
}

void StateManager::PushIdleState(const str_type::string& name, const StatePtr& state)
{
	m_idleStates[name] = state;
}

void StateManager::SetState(const str_type::string& name)
{
	std::map<gs2d::str_type::string, StatePtr>::iterator iter = m_idleStates.find(name);
	if (iter != m_idleStates.end())
	{
		m_nextState = iter->second;
	}
}

void StateManager::SetState(const StatePtr& state)
{
	m_nextState = state;
}

StatePtr StateManager::GetCurrentState()
{
	return m_currentState;
}
