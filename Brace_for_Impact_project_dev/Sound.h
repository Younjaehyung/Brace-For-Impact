#pragma once
#include "fmod/inc/fmod.hpp"
#include "fmod/inc/fmod_errors.h"
#pragma comment(lib,"fmod/lib/x64/fmod_vc.lib")
#include <iostream>
#include <string>

//system은 다이렉트 디바이스와 유사하다. 사운드 시스템.
//sound은 사운드 포인터로 실제 사운드 메모리이다.
//channel은 최대 32채널을 갖고 중복적으로 실행이 되기 위해서 필요함.
//(오디오 채널)


//https://dlemrcnd.tistory.com/73 [출처]

class Sound {
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
	Sound* GetSoundID ( std::string filename );
	Sound* CreateSound ( std::string filename );
	
	Sound* FindSoundlist (std::string filename );
	

	static SoundManager& getInstance ( ) {
		static SoundManager instance;
		return instance;
	}
private:
	FMOD::System* m_pSystem = nullptr;
	std::unordered_map<std::string , Sound*> Channel;

	FMOD_RESULT result;
};




bool SoundManager::Init ( ) {
	FMOD_RESULT ret;
	//FMOD 시스템 디바이스 생성

	ret = FMOD::System_Create ( &m_pSystem );
	if ( ret != FMOD_OK ) {
		return false;
	}

	ret = m_pSystem->init ( 32 , FMOD_INIT_NORMAL , 0 );
	if ( ret != FMOD_OK ) {
		return false;
	}

	CreateSoundlist ( );
	
}

inline void SoundManager::CreateSoundlist ( ) {
	Channel.emplace ( "testMP3" , CreateSound ( "Whale_06_R.P.G._Shine.mp3" ) );



}

Sound* SoundManager::FindSoundlist ( std::string filename ) {
	auto it = Channel.find ( filename );
	if ( it != Channel.end ( ) ) {
		return it->second;
	}
	return nullptr;
}

Sound* SoundManager::CreateSound ( std::string filename ) {
	FMOD::Sound* newSound = nullptr;
	m_pSystem->createSound ( filename.c_str() , FMOD_LOOP_OFF , 0 , &newSound );

	Sound* createsound = new Sound;
	createsound->GetData (newSound, m_pSystem );

	if ( result != FMOD_OK ) {
		std::cerr << filename << std::endl;
	}

	return createsound;

}

Sound* SoundManager::GetSoundID ( std::string filename ) {
	auto it = Channel.find ( filename );
	if ( it != Channel.end ( ) ) {
		return it->second ;  // 찾은 Sound 객체의 주소 반환
	}
	return nullptr;  // 해당 파일명이 없을 때
}



inline void Sound::playSound ()
{
	FMOD::Channel* newChannel = nullptr;
	result = m_pSystem->playSound ( Soundfile , 0 , false , &newChannel );
	Channel = newChannel;


	
}




void Sound:: PauseSound ( ) {
	
	if ( Channel != nullptr ) {
		bool isPaused;
		Channel->getPaused ( &isPaused );
		Channel->setPaused ( !isPaused ); // 현재 상태에 따라 재생/일시 정지 전환
	}
}

void Sound::ReplaySound () {
	
	if ( Channel != nullptr ) {
		bool isPlaying = false;
		Channel->isPlaying ( &isPlaying );  // 현재 재생 중인지 확인

		if ( !isPlaying ) {
			// 사운드가 끝났으므로 위치를 처음으로 설정
			unsigned int position = 0;
			Channel->setPosition ( position , FMOD_TIMEUNIT_MS ); // 위치를 처음으로 설정
			playSound ( );  // 사운드 재생
		}
	}
}

inline void Sound::GetData ( FMOD::Sound* SoundID, FMOD::System* m_pSystemID )
{
	m_pSystem = m_pSystemID;
	Soundfile = SoundID;
	Channel = nullptr;
}



void Sound::SetVolume ( float volume ) {
	
	if ( Channel != nullptr ) {
		Channel->setVolume ( volume );
	}
}




inline void SoundManager::PlayingSound ( )
{

	m_pSystem->update ( );
	
	/*while ( 1 ) {
		result = m_pSystem->update ( );
		if ( result != FMOD_OK )
			return;
	
		if ( m_pChannel ) {
			bool playing = false;
			result = m_pChannel->isPlaying ( &playing );
			if ( !playing )break;

		}
	
	}*/
}


