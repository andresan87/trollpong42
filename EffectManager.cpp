#include "EffectManager.h" 

using namespace gs2d;
using namespace gs2d::math;

void EffectManager::Add(TemporaryEffectPtr effect)
{
	m_effects.push_back(effect);
}

void EffectManager::Update(VideoPtr video, const unsigned long elapsedTime)
{
	for (std::list<TemporaryEffectPtr>::iterator iter = m_effects.begin(); iter != m_effects.end();)
	{
		if ((*iter)->IsOver())
		{
			iter = m_effects.erase(iter);
		}
		else
		{
			(*iter)->Update(video, elapsedTime);
			 iter++;
		}
	}
}

void EffectManager::Draw(VideoPtr video)
{
	for (std::list<TemporaryEffectPtr>::iterator iter = m_effects.begin(); iter != m_effects.end(); iter++)
	{
		(*iter)->Draw(video);
	}
}