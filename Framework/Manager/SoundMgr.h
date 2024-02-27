#pragma once
#include "Singleton.h"
class SoundMgr : public Singleton<SoundMgr>
{

	friend Singleton<SoundMgr>;
private:

	SoundMgr();
	virtual ~SoundMgr();

	//�÷��� ����Ʈ ����� �߰��ϸ� ���� �� ����.
	sf::Sound bgm[2];
	int frontBGMIndex = 0;
	int backBGMIndex = 1;

	bool isFading = false;
	float fadeDuration = 5.f;
	float fadeTimer = 0.f;
	float frontMixingSpeed = 0.f;
	float backMixingSpeed = 0.f;

	std::list<sf::Sound*> playing;
	std::list<sf::Sound*> waiting;


	float sfxVolume = 100.f;
	float bgmVolume = 100.f;
	float uiVolume = 100.f;
	bool mute = false;

public:
	void Init(int totalChannels = 32);
	void Release();

	void Update(float dt);
	
	void PlayBGM(const std::string& id, bool loop = true, bool crossFade = true);
	void StopBGM(const std::string& id);
	void MixingBGM(float dt);
	
	void PlaySfx(const std::string& id, bool loop = false);
	void PlaySfx(sf::SoundBuffer& buffer, bool loop = false);
	void StopAllSfx();


	//0.0f ~ 100.f
	void SetVolumeSfx(float value);
	void UpVolumeSfx(float value);
	void DownVolumeSfx(float value);
	//0.0f ~ 100.f
	void SetVolumeBGM(float value);
	void UpVolumeBGM(float value);
	void DownVolumeBGM(float value);

	size_t GetPlayingCount() { return playing.size(); }
	size_t GetWaitingCount() { return waiting.size(); }


	void NewPlayBGM(std::string id, bool crossFade = true);
	void NewFading(float dt);

};


#define SOUND_MGR (Singleton<SoundMgr>::Instance())