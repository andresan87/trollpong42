#ifndef AUDIO_RESOURCE_MANAGER_H_
#define AUDIO_RESOURCE_MANAGER_H_

#include "../gs2d/src/gs2dframework.h"
#include <map>

class AudioResourceManager
{
	std::map<gs2d::str_type::string, gs2d::AudioSamplePtr> m_samples;
	static const gs2d::str_type::string m_defaultAudioPath;

public:

	void ReleaseAll();
	gs2d::AudioSamplePtr operator[] (const gs2d::str_type::string& fileName);
	gs2d::AudioSamplePtr GetSample(const gs2d::AudioPtr& audio, const gs2d::str_type::string& fileName);
};

#endif
