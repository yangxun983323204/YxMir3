#include "SoundMgr.h"
#include <io.h>


SoundMgr::SoundMgr()
{
	LoadWaveFileList("SoundList.wwl");
	LoadBgmFileList("BgmList.wwl");
}


SoundMgr::~SoundMgr()
{
	if (_bgmListHeader) delete _bgmListHeader;
	if (_bgmFileList) delete[] _bgmFileList;
	
	if (_waveList){
		for (int i = 0; i < _waveListHeader->FieldCount; i++)
		{
			delete _waveList[i];
		}
		delete[] _waveList;
	}
	if (_waveListHeader) delete _waveListHeader;
}

bool SoundMgr::GetBgmFileName(char * mapName, char * mp3Name)
{
	for (int i = 0; i < _bgmListHeader->FieldCount; i++)
	{
		if (_bgmFileList[i]=='[')
		{
			i++;
			if (strcmp(_bgmFileList+i,mapName)==0)
			{
				i += strlen(mapName);
				while (_bgmFileList[i] == 0)
					i++;
				strcpy(mp3Name, _bgmFileList + i);
				return true;
			}
		}
	}
	return false;
}

void SoundMgr::LoadBgmFileList(string fileName)
{
	auto file = fopen(fileName.c_str(), "rb");
	if (file)
	{
		int size = filelength(fileno(file));
		_bgmListHeader = new WaveListHeader();
		fread(_bgmListHeader, sizeof(WaveListHeader), 1, file);
		int count = size - sizeof(WaveListHeader);
		_bgmFileList = new char[count];
		_bgmListHeader->FieldCount = count;
		fread(_bgmFileList, sizeof(char), count, file);
		fclose(file);
	}
}

void SoundMgr::LoadWaveFileList(string fileName)
{
	auto file = fopen(fileName.c_str(), "rb");
	if (file) 
	{
		_waveListHeader = new WaveListHeader();
		fread(_waveListHeader, sizeof(WaveListHeader), 1, file);
		_waveList = new WaveListNode*[_waveListHeader->FieldCount];
		int count = 0;
		for (int i = 0; i < _waveListHeader->ListCount; i++)
		{
			auto node = new WaveListNode();
			memset(node, 0, sizeof(WaveListNode));
			fread(node, sizeof(WaveListNode), 1, file);
			if (node->ID!=0)
			{
				char temp[4];
				temp[3] = 0;
				for (int j = 0; j < strlen(node->Des); j++)// Îªc×Ö·û´®½áÎ²²åÈë'0'
				{
					strncpy(temp, node->Des + j, 3);
					if (strcmp(temp,"wav") == 0)
					{
						*(node->Des + j + 3) = 0;
					}
				}
				_waveList[count++] = node;
			}
			else
			{
				delete node;
			}
		}
		fclose(file);
	}
}

char * SoundMgr::SeekWaveFile(int wavNum)
{
	for (uint32_t i = 0; i < _waveListHeader->FieldCount; i++)
	{
		if (wavNum == _waveList[i]->ID)
			return _waveList[i]->Des;
	}
	return nullptr;
}
