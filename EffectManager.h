#ifndef EFFECT_MANAGER_H_
#define EFFECT_MANAGER_H_

#include "../gs2d/src/gs2dframework.h"
#include "TemporaryEffect.h"
#include <list>

class EffectManager
{
	std::list<TemporaryEffectPtr> m_effects;

public:
	void Add(TemporaryEffectPtr effect);
	void Update(gs2d::VideoPtr video, const unsigned long elapsedTime);
	void Draw(gs2d::VideoPtr video);
};

typedef boost::shared_ptr<EffectManager> EffectManagerPtr;

#endif