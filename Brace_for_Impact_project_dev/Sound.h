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
	std::unordered_map<std::string, std::pair<FMOD::Sound*, FMOD::Channel*>> SoundChannel;

	FMOD_RESULT result;

	unsigned int MID;
	bool Init ( );
	void playSound ( std::string filename );
	void CreateSoundlist ( );
	void PlayingSound ( );
	void PauseSound ( std::string filename );
	void SetVolume ( std::string filename , float volume );
	FMOD::Sound* FindSoundlist (std::string filename );
	FMOD::Sound* CreateSound (std::string filename );
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

inline void SoundManager::CreateSoundlist ( ) {
	SoundChannel.emplace ( "testMP3" , CreateSound ( "Whale_06_R.P.G._Shine.mp3" ) );



}

FMOD::Sound* SoundManager::FindSoundlist ( std::string filename ) {
	auto it = SoundChannel.find ( filename );
	if ( it != SoundChannel.end ( ) ) {
		return it->second.first;
	}
	return nullptr;
}

inline void SoundManager::playSound (std::string filename )
{
	FMOD::Channel* newChannel = nullptr;
	result = m_pSystem->playSound ( FindSoundlist(filename ) , 0 , false , &newChannel );
	SoundChannel.find ( filename )->second.second = newChannel;


	if ( result != FMOD_OK ) {
		std::cerr << filename<<" : play sound err" << std::endl;
	}
}

void SoundManager :: PauseSound ( std::string filename ) {
	FMOD::Channel* channel = SoundChannel.find ( filename )->second.second;
	if ( channel != nullptr ) {
		bool isPaused;
		channel->getPaused ( &isPaused );
		channel->setPaused ( !isPaused ); // 현재 상태에 따라 재생/일시 정지 전환
	}
}

void ReplaySound ( int soundID ) {
	FMOD::Channel* channel = channelMap[ soundID ];
	if ( channel != nullptr ) {
		bool isPlaying = false;
		channel->isPlaying ( &isPlaying );  // 현재 재생 중인지 확인

		if ( !isPlaying ) {
			// 사운드가 끝났으므로 위치를 처음으로 설정
			unsigned int position = 0;
			channel->setPosition ( position , FMOD_TIMEUNIT_MS ); // 위치를 처음으로 설정
			PlaySound ( soundID );  // 사운드 재생
		}
	}
}



void SoundManager::SetVolume ( std::string filename , float volume ) {
	FMOD::Channel* channel = SoundChannel.find ( filename )->second.second; // 채널 가져오기
	if ( channel != nullptr ) {
		channel->setVolume ( volume );
	}
}


FMOD::Sound* SoundManager::CreateSound (std::string filename ) {
	FMOD::Sound* newSound = nullptr;
	m_pSystem->createSound ( "filename" , FMOD_LOOP_OFF , 0 , &newSound );

	if ( result != FMOD_OK ) {
		std::cerr << filename << std::endl;
	}

	return newSound;

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


