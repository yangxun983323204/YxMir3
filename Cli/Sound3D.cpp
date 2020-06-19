#include "Sound3D.h"

Sound3D::Sound3D()
{
	Is3D = true;
	_wav = nullptr;
	_dirty = true;
	_mgr = SoundMgr::Instance();
	_isPlaying = false;
}


Sound3D::~Sound3D()
{
	Stop();
	if (_wav) {
		Mix_FreeChunk(_wav);
		_wav = nullptr;
	}
}

void Sound3D::LoadWave(int num)
{
	string file =  _mgr->SeekWaveFile(num);
	LoadWave("./Sound/"+file);
}

void Sound3D::LoadWave(string file)
{
	if (_isPlaying)
		Stop();

	if (_wav) {
		Mix_FreeChunk(_wav);
		_wav = nullptr;
	}
	_wav = Mix_LoadWAV(file.c_str());
}

void Sound3D::Play(bool loop)
{
	_isPlaying = _mgr->PlaySound(this, loop, &_channel);
}

void Sound3D::Stop()
{
	if (_isPlaying)
	{
		_mgr->StopSound(_channel);
		_isPlaying = false;
	}
}

void Sound3D::UpdatePos(Vector2Float pos)
{
	_pos = pos;
	_dirty = true;
}

void Sound3D::OnSoundFinished()
{
	_isPlaying = false;
}
