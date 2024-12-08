#pragma once
#include "fmod.h"
#include "Base.h"


BEGIN(Engine)

#define MAX_CHANNEL 512

class CSound_Manager final : public CBase
{
	DECLARE_SINGLETON(CSound_Manager);

private:
	CSound_Manager();
	~CSound_Manager();

public:
	void Initialize();
	void Release();

public:
	int  VolumeUp(CHANNELID eID, _float _vol);
	int  VolumeDown(CHANNELID eID, _float _vol);
	int  BGMVolumeUp(_float _vol);
	int  BGMVolumeDown(_float _vol);
	int  Pause(CHANNELID eID);
	_uint PlaySound(TCHAR* pSoundKey, _uint _iIndex, _float _vol);
	_uint PlaySound(TCHAR* pSoundKey, _float _vol);
	void PlayBGM(TCHAR* pSoundKey, _float _vol);
	void StopSound(_uint _iChannelIndex);
	void StopAll();

private:
	float m_volume = SOUND_DEFAULT;
	float m_BGMvolume = SOUND_DEFAULT;
	FMOD_BOOL m_bool;

private:
	void LoadSoundFile();

private:
	// ���� ���ҽ� ������ ���� ��ü 
	map<TCHAR*, FMOD_SOUND*> m_mapSound;
	// FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 
	FMOD_CHANNEL* m_pChannelArr[MAX_CHANNEL];
	// ���� ,ä�� ��ü �� ��ġ�� �����ϴ� ��ü 
	FMOD_SYSTEM* m_pSystem;
	_bool		m_bPause = false;

public:
	virtual void Free() override;
};

END