#include "AudioResourceManager.h"

using namespace gs2d;
using namespace gs2d::math;

const str_type::string AudioResourceManager::m_defaultAudioPath = GS_L("assets/soundfx/");

AudioSamplePtr AudioResourceManager::GetSample(const AudioPtr& audio, const str_type::string& fileName)
{
	std::map<str_type::string, AudioSamplePtr>::iterator iter = m_samples.find(fileName);
	if (iter == m_samples.end())
	{
		AudioSamplePtr sample = audio->LoadSampleFromFile(m_defaultAudioPath + fileName, GSST_SOUND_EFFECT);
		if (sample)
		{
			m_samples[fileName] = sample;
			return sample;
		}
		else
		{
			return AudioSamplePtr();
		}
	}
	else
	{
		return iter->second;
	}
}

void AudioResourceManager::ReleaseAll()
{
	m_samples.clear();
}

AudioSamplePtr AudioResourceManager::operator[] (const str_type::string& fileName)
{
	std::map<str_type::string, AudioSamplePtr>::iterator iter = m_samples.find(fileName);
	if (iter == m_samples.end())
	{
		return iter->second;
	}
	else
	{
		return AudioSamplePtr();
	}
}
