// 3D“Ù–ß µœ÷
#pragma once
#include "Common.h"
#include "SDLInc.h"
#include "SoundMgr.h"

class Sound3D
{
	friend class SoundMgr;
public:
	bool Is3D;
	Sound3D();
	~Sound3D();
	void LoadWave(int num);
	void LoadWave(string file);
	void Play(bool loop);
	void Stop();
	void UpdatePos(Vector2Float pos);
	
private:
	Vector2Float _pos;
	Mix_Chunk *_wav;
	int _channel;
	SoundMgr *_mgr;
	bool _isPlaying;
	bool _dirty;

	void OnSoundFinished();
};

