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

class SoundManager {
public:
	FMOD::System* m_pSystem = nullptr;
	std::map<std::string, FMOD::Sound*> m_pSound;

	std::map<std::string, FMOD::Channel*>  m_pChannel;
	FMOD_RESULT result;

	unsigned int MID;
	bool Init ( );
	void playSound ( );
	void CreateSoundlist ( );
	void PlayingSound ( );
	unsigned int CreateSound (std::string filename );
	static SoundManager& getInstance ( ) {
		static SoundManager instance;
		return instance;
	}
private:

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



inline void SoundManager::playSound ( )
{
	result = m_pSystem->playSound ( m_pSound , 0 , false , &m_pChannel );
}



inline void SoundManager::CreateSoundlist ( ){
	m_pSound.emplace("testMP3" , CreateSound ( "Whale_06_R.P.G._Shine.mp3" );
	
	

}

unsigned int SoundManager::CreateSound (std::string filename ) {
	m_pSystem->createSound ( "filename" , FMOD_LOOP_OFF , 0 , &m_pSound );

	if ( result != FMOD_OK ) {
		std::cerr << filename << std::endl;
	}

	

	return MID++;
}

inline void SoundManager::PlayingSound ( )
{
	playSound ( );
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


