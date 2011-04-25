#include "GameState.h"

#include <sstream>

gs2d::BaseApplicationPtr gs2d::CreateBaseApplication()
{
	return BaseApplicationPtr(new StateManager(StatePtr(new GameState())));
}
