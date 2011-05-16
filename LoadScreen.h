#ifndef LOAD_SCREEN_H_
#define LOAD_SCREEN_H_

#include "StateManager.h"
#include "SpriteResourceManager.h"

class AbstractState
{
public:
	virtual void SetState() = 0;
};
typedef boost::shared_ptr<AbstractState> AbstractStatePtr;

class ExistingState : public AbstractState
{
	gs2d::str_type::string m_state;
public:
	ExistingState(const gs2d::str_type::string& state);
	void SetState();
};
typedef boost::shared_ptr<ExistingState> ExistingStatePtr;

class NewState : public AbstractState
{
	StatePtr m_state;
public:
	NewState(StatePtr state);
	void SetState();
};
typedef boost::shared_ptr<NewState> NewStatePtr;

class LoadScreen : public State
{
	const AbstractStatePtr m_nextState;
	const gs2d::str_type::string m_text;
	const gs2d::str_type::string m_font;
	const gs2d::str_type::string m_background;
	const gs2d::GS_COLOR m_color;
	gs2d::math::Vector2 m_textSize;
	//gs2d::ShaderPtr m_shader;

public:
	LoadScreen(AbstractStatePtr nextState, const gs2d::str_type::string& text, const gs2d::GS_COLOR color,
			   const gs2d::str_type::string& font, const gs2d::str_type::string& background);
	void LoadResources(SpriteResourceManager &spr, gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio);
	void Update(SpriteResourceManager &spr, unsigned long lastFrameDeltaTimeMS, gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio);
	void Draw(SpriteResourceManager &spr, gs2d::VideoPtr video, gs2d::InputPtr input, gs2d::AudioPtr audio);
};

#endif