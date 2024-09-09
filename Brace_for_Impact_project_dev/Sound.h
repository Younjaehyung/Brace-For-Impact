#pragma once
#pragma comment(lib,"fmod/lib/x64/fmod_vc.lib")
#include "fmod/inc/fmod.hpp"
#include "fmod/inc/fmod_errors.h"
#include <iostream>
#include <string>
#include <unordered_map>
//system은 다이렉트 디바이스와 유사하다. 사운드 시스템.
//sound은 사운드 포인터로 실제 사운드 메모리이다.
//channel은 최대 32채널을 갖고 중복적으로 실행이 되기 위해서 필요함.
//(오디오 채널)


//https://dlemrcnd.tistory.com/73 [출처]

class Sounds {
	FMOD::System* m_pSystem;
	FMOD::Sound* Soundfile;
	FMOD::Channel* Channel;
	FMOD_RESULT result;
public:

	void playSound ( );
	void PauseSound ( );
	void SetVolume ( float volume );
	void ReplaySound ( );
	void GetData ( FMOD::Sound*, FMOD::System* m_pSystem );
};



class SoundManager  {
public:
	

	unsigned int MID;
	bool Init ( );
	
	void CreateSoundlist ( );
	void PlayingSound ( );
	Sounds* GetSoundID ( std::string filename );
	Sounds* CreateSound ( std::string filename );
	
	Sounds* FindSoundlist (std::string filename );
	

	static SoundManager& getInstance ( ) {
		static SoundManager instance;
		return instance;
	}
private:
	SoundManager ( ) {
		FMOD::System* m_pSystem = nullptr;
	};
	FMOD::System* m_pSystem;
	std::unordered_map<std::string , Sounds*> Channel;

	FMOD_RESULT result;
};



