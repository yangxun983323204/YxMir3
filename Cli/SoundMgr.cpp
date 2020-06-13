#include "SoundMgr.h"
#include <io.h>


SoundMgr::SoundMgr()
{
	Mix_Init(MIX_INIT_FLAC|MIX_INIT_OGG|MIX_INIT_MP3);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
	LoadWaveFileList("SoundList.wwl");
	LoadBgmFileList("BgmList.wwl");
	_bgmMusic = nullptr;
	_Fx = nullptr;
}

SoundMgr::~SoundMgr()
{
	if (_bgmListHeader) delete _bgmListHeader;
	if (_bgmFileList) delete[] _bgmFileList;
	
	if (_waveList){
		for (uint32_t i = 0; i < _waveListHeader->FieldCount; i++)
		{
			delete _waveList[i];
		}
		delete[] _waveList;
	}
	if (_waveListHeader) delete _waveListHeader;
	//
	if (_bgmMusic) {
		BgmFadeOut(0);
		Mix_FreeMusic(_bgmMusic);
		_bgmMusic = nullptr;
	}
	if (_Fx)
	{
		_Fx->Stop();
		delete _Fx;
		_Fx = nullptr;
	}
	
	Mix_CloseAudio();
	Mix_Quit();
}

bool SoundMgr::GetBgmFileName(char * mapName, char * mp3Name)
{
	for (uint32_t i = 0; i < _bgmListHeader->FieldCount; i++)
	{
		if (_bgmFileList[i]=='[')
		{
			i++;
			if (strcmp(_bgmFileList+i,mapName)==0)
			{
				i += (int)strlen(mapName);
				while (_bgmFileList[i] == 0)
					i++;
				strcpy(mp3Name, _bgmFileList + i);
				return true;
			}
		}
	}
	return false;
}

void SoundMgr::PlayEffect(char * wavFile, uint32_t fade, bool loop)
{
	if (_Fx==nullptr)
		_Fx = new Sound3D();

	_Fx->Stop();
	string path = "./Sound/";
	path +=wavFile;
	_Fx->LoadWave(path);
	_Fx->Is3D = false;
	_Fx->Play(loop);
}

void SoundMgr::PlayMusic(char * fileName,uint32_t fade, bool loop)
{
	string path = fileName;
	path = "./Sound/" + path;
	if(_bgmMusic){
		BgmFadeOut(0);
		Mix_FreeMusic(_bgmMusic);
		_bgmMusic = nullptr;
	}
	_bgmMusic = Mix_LoadMUS(path.c_str());
	BgmFadeIn(fade, loop);
}

void SoundMgr::PlayBgm(char * mapName, bool loop)
{
	char mp3[10];
	GetBgmFileName(mapName, mp3);
	PlayMusic(mp3,5000,loop);
}

void SoundMgr::StopBgm()
{
	BgmFadeOut(5000);
}

void SoundMgr::Update()
{
	for each (auto kv in _sounds)
	{
		Sound3D *sound = kv.second;
		if (sound && sound->_isPlaying && sound->Is3D)
		{
			int rawAngle = (int(atan2(sound->_pos.y - Pos.y, sound->_pos.x - Pos.x) * Rad2Deg) + 360) % 360;
			int clockwizeAngle = (rawAngle + 90) % 360;
			Mix_SetPosition((int)kv.first, clockwizeAngle, Vector2UInt::Distance(Pos, sound->_pos));
		}
	}
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
		for (uint32_t i = 0; i < _waveListHeader->ListCount; i++)
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

void SoundMgr::BgmFadeIn(uint32_t ms,bool loop)
{
	Mix_FadeInMusic(_bgmMusic, loop ? -1 : 0, ms);
}

void SoundMgr::BgmFadeOut(uint32_t ms)
{
	if (!Mix_PlayingMusic())
		return;
	Mix_FadeOutMusic(ms);
}

bool SoundMgr::PlaySound(Sound3D * sound, bool loop, int * channel)
{
	*channel = Mix_PlayChannel(-1, sound->_wav, loop);
	if (*channel < 0)
		return false;
	else {
		_sounds[*channel] = sound;
		return true;
	}
}

void SoundMgr::StopSound(const int &channel)
{
	if (Mix_Playing(channel))
	{
		Mix_FadeOutChannel(channel, 0);
		_sounds[channel] = nullptr;
	}
}

void SoundMgr::OnChannelFinished(int channel)
{
	auto sound = Instance()->_sounds[channel];
	if (sound)
		sound->OnSoundFinished();
}
