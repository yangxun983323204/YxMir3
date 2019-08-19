#pragma once
#include <stdint.h>
#include <string>
#include <map>

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
	// 解析一些奇奇怪怪的文件格式
	bool GetBgmFileName(char *mapName, char *mp3Name);
private:
	WaveListHeader *_bgmListHeader;
	char *_bgmFileList;
	WaveListHeader *_waveListHeader;
	WaveListNode **_waveList;


	void LoadBgmFileList(string fileName);
	void LoadWaveFileList(string fileName);
	char* SeekWaveFile(int wavNum);
};

