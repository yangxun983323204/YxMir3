#pragma once
#include <stdint.h>
#include <string>
#include <map>
#include "SDLInc.h"
#include "Singleton.hpp"
#include "Sound3D.h"

using std::string;

#pragma pack(1)
struct WaveListNode
{
	int16_t ID;
	char Des[14];
};

struct WaveListHeader
{
	char Title[40];
	char TargetDir[10];
	uint32_t FieldCount;
	uint32_t ListCount;
};
#pragma pack()

class SoundMgr:
	public Singleton<SoundMgr>
{
	friend class Sound3D;
public:
	Vector2UInt Pos;
	SoundMgr();
	~SoundMgr();
	// 解析一些奇奇怪怪的文件格式
	bool GetBgmFileName(char *mapName, char *mp3Name);
	void PlayMusic(char* fileName, bool loop);
	void PlayBgm(char* mapName,bool loop);
	void StopBgm();
	void Update();
private:
	void LoadBgmFileList(string fileName);
	void LoadWaveFileList(string fileName);
	char* SeekWaveFile(int wavNum);
	void BgmFadeIn(uint32_t ms, bool loop);
	void BgmFadeOut(uint32_t ms);
	bool PlaySound(Sound3D *sound, bool loop, __out int *channel);
	void StopSound(const int &channel);

private:
	WaveListHeader *_bgmListHeader;
	char *_bgmFileList;
	WaveListHeader *_waveListHeader;
	WaveListNode **_waveList;
	Mix_Music *_bgmMusic;
	std::map<uint32_t, Sound3D*> _sounds;
	static void OnChannelFinished(int channel);
};

