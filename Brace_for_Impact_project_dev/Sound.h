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

	void playSound ( );	//음악재생 => 무조건 이걸 한번 해야지 나중에 다시 틀거나 멈추기가 가능함
	void PauseSound ( ); //음악중지 => 현재 음악 중지
	void SetVolume ( float volume ); //함수 인자로 숫자넣어주면 해당 값만큼 소리를 바꿔줌
	void ReplaySound ( ); //음악재반복, 같은 음원파일이면 이걸 실행시키면 음원을 처음부터 다시 재생시켜줌
	void GetData ( FMOD::Sound*, FMOD::System* m_pSystem ); //내부 기능을 위한 함수임. 무시하삼.
	FMOD::Channel* GetChannel(){ return Channel; }
};



class SoundManager  {
public:

	unsigned int MID;
	bool Init ( );
	
	void CreateSoundlist ( );
	void PlayingSound ( );
	Sounds* GetSoundID ( std::string filename );
	Sounds* CreateSound ( std::string filename,int mode );
	void StopAllChannels ();
	Sounds* FindSoundlist (std::string filename );
	

	static SoundManager& getInstance ( ) {
		static SoundManager instance;
		return instance;
	}
private:
	SoundManager ( ) {
		FMOD::System* m_pSystem = nullptr;
		SoundChannelCount = 0;
	};
	FMOD::System* m_pSystem;
	std::unordered_map<std::string , Sounds*> Channel;

	FMOD_RESULT result;
	int SoundChannelCount;
};



