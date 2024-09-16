#include "Sound.h"


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
	//기본 음원을 넣는 포멧. 마지막에 숫자 0 : 음원루프x /숫자 1 : 음원루프O
	Channel.emplace ( "testMP3" , CreateSound ( "Whale_06_R.P.G._Shine.mp3",1 ) );
	Channel.emplace ( "Explosion" , CreateSound ( "BFI_Explosion.wav" , 0 ) );
	Channel.emplace ( "Menu" , CreateSound ( "BFI_Menu.wav" , 0 ) );
	Channel.emplace ( "Hit" , CreateSound ( "BFI_Hit.mp3" , 0 ) );
	Channel.emplace ( "Start" , CreateSound ( "BFI_Start.wav" , 0 ) );
	Channel.emplace ( "Shoot" , CreateSound ( "BFI_Shoot.wav" , 0 ) );
	Channel.emplace ( "Item" , CreateSound ( "BFI_Item.wav" , 0 ) );
	Channel.emplace ( "Laser" , CreateSound ( "BFI_Laser.wav" , 0 ) );
}

Sounds* SoundManager::FindSoundlist ( std::string filename ) {
	auto it = Channel.find ( filename );
	if ( it != Channel.end ( ) ) {
		return it->second;
	}
	return nullptr;
}

Sounds* SoundManager::CreateSound ( std::string filename,int mode=0 ) {
	FMOD::Sound* newSound = nullptr;
	m_pSystem->createSound ( filename.c_str ( ) , FMOD_LOOP_OFF+mode , 0 , &newSound );
	
	Sounds* createsound = new Sounds;
	createsound->GetData ( newSound , m_pSystem );

	if ( result != FMOD_OK ) {
		std::cerr << filename << std::endl;
	}

	return createsound;

}

Sounds* SoundManager::GetSoundID ( std::string filename ) {
	auto it = Channel.find ( filename );
	if ( it != Channel.end ( ) ) {
		return it->second;  // 찾은 Sound 객체의 주소 반환
	}
	return nullptr;  // 해당 파일명이 없을 때
}


void SoundManager::StopAllChannels () {
	for ( auto& pair : Channel ) {
		FMOD::Channel* channel = pair.second->GetChannel();
		if ( channel ) {
			channel->stop ( );
		}
	}
	std::cerr << Channel.size ( ) << std::endl;
}


inline void Sounds::playSound ( )
{
	FMOD::Channel* newChannel = nullptr;
	result = m_pSystem->playSound ( Soundfile , 0 , false , &newChannel );
	Channel = newChannel;



}

void Sounds::PauseSound ( ) {

	if ( Channel != nullptr ) {
		bool isPaused;
		Channel->getPaused ( &isPaused );
		Channel->setPaused ( !isPaused ); // 현재 상태에 따라 재생/일시 정지 전환
	}
}

void Sounds::ReplaySound ( ) {

	if ( Channel != nullptr ) {
		bool isPlaying = false;
		Channel->isPlaying ( &isPlaying );  // 현재 재생 중인지 확인
		unsigned int position = 0;
		Channel->stop ( );
		Channel->setPosition ( position , FMOD_TIMEUNIT_MS ); // 위치를 처음으로 설정
		playSound ( );  // 사운드 재생
		//if ( !isPlaying ) {
		//	// 사운드가 끝났으므로 위치를 처음으로 설정
		//	
		//	Channel->setPosition ( position , FMOD_TIMEUNIT_MS ); // 위치를 처음으로 설정
		//	playSound ( );  // 사운드 재생
		//}
		//else {
		//	Channel->setPosition ( position , FMOD_TIMEUNIT_MS );
		//}
	}
	else {
		playSound ( );
	}
}



inline void Sounds::GetData ( FMOD::Sound* SoundID , FMOD::System* m_pSystemID )
{
	m_pSystem = m_pSystemID;
	Soundfile = SoundID;
	Channel = nullptr;
}



void Sounds::SetVolume ( float volume ) {

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


