#include "GameState.h"
#include "GameMenu.h"

#include <sstream>

gs2d::BaseApplicationPtr gs2d::CreateBaseApplication()
{
	return BaseApplicationPtr(new StateManager(StatePtr(new GameMenu)));
}
