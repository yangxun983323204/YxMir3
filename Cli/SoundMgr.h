#pragma once
#include <stdint.h>
#include <string>
#include <map>
#include "SDLInc.h"

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

class SoundMgr
{
public:
	SoundMgr();
	~SoundMgr();
	// ����һЩ����ֵֹ��ļ���ʽ
	bool GetBgmFileName(char *mapName, char *mp3Name);
	void PlayBgm(char* mapName,bool loop);
	void StopBgm();
private:
	WaveListHeader *_bgmListHeader;
	char *_bgmFileList;
	WaveListHeader *_waveListHeader;
	WaveListNode **_waveList;


	void LoadBgmFileList(string fileName);
	void LoadWaveFileList(string fileName);
	char* SeekWaveFile(int wavNum);
	void BgmFadeIn(uint32_t ms, bool loop);
	void BgmFadeOut(uint32_t ms);

	Mix_Music *_bgmMusic;
	Mix_Chunk *_wav;
};
