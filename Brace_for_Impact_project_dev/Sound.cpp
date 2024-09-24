#include "Sound.h"


bool SoundManager::Initialize ( ) {
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
	Channel.emplace ( "Stage1" , CreateSound ( "BFI_ST_1_The Origin.wav" , 1 ));
	Channel.emplace ( "Stage2" , CreateSound ( "BFI_ST_2_8bit Dungeon Bossc.wav" , 1 ));
	Channel.emplace ( "Stage3" , CreateSound ( "BFI_ST_3_Funk Modulator.wav" , 1 ));
	Channel.emplace ( "Stage4" , CreateSound ( "BFI_ST_4_Scrub Slayer.wav" , 1 ));
	Channel.emplace ( "Stage5" , CreateSound ( "BFI_ST_5_Welcome Player.wav" , 1 ));
	Channel.emplace( "Stage6", CreateSound ("BFI_ST6_The_FinalBattle.mp3" , 1 ) );
	Channel.emplace ( "Title" , CreateSound ( "BFI_Title_Good Old Times.wav" , 1 ) );
	Channel.emplace ( "Dash" , CreateSound ( "BFI_Dash.wav" , 0 ) );
	Channel.emplace ( "Reload" , CreateSound ( "BFI_Reload.wav" , 0 ) );
	Channel.emplace ( "Move" , CreateSound ( "BFI_Move.mp3" , 0 ) );
	Channel.emplace ( "Clear" , CreateSound ( "BFI_GameClear.wav" , 0 ) );
	Channel.emplace ( "Over" , CreateSound ( "BFI_Gameover.wav" , 1 ) );
	Channel.emplace ( "Trim" , CreateSound ( "BFI_monster_trim1.mp3" , 0 ) );
	Channel.emplace ( "Trim2" , CreateSound ( "BFI_monster_trim2.mp3" , 0 ) );
	Channel.emplace ( "angry" , CreateSound ( "BFI_monster_angry.mp3" , 0 ) );
	Channel.emplace ( "missile1" , CreateSound ( "BFI_monster_missile.mp3" , 0 ) );
	Channel.emplace ( "missile2" , CreateSound ( "BFI_monster_missile2.mp3" , 0 ) );
	Channel.emplace ( "ele" , CreateSound ( "BFI_monster_ele.mp3" , 0 ) );
	Channel.emplace ( "cine" , CreateSound ( "BFI_monster_Cinematic.mp3" , 0 ) );
	Channel.emplace ( "stomp1" , CreateSound ( "BFI_monster_stomp1.mp3" , 0 ) );
	Channel.emplace ( "stomp2" , CreateSound ( "BFI_monster_stomp2.mp3" , 0 ) );
	Channel.emplace ( "stomp3" , CreateSound ( "BFI_monster_stomp3.mp3" , 0 ) );
	Channel.emplace ( "cute" , CreateSound ( "BFI_monster_cute.mp3" , 0 ) );
	Channel.emplace ( "bip" , CreateSound ( "BFI_monster_bipbip.mp3" , 0 ) );
	Channel.emplace ( "charge" , CreateSound ( "BFI_monster_Charge.mp3" , 0 ));
}

void SoundManager::Update ( )
{
	m_pSystem->update ( );

}

Sounds* SoundManager::FindSoundlist ( std::string filename ) {
	auto it = Channel.find ( filename );
	if ( it != Channel.end ( ) ) {
		return it->second;
	}
	return nullptr;
}

Sounds* SoundManager::CreateSound ( std::string filename,int mode) {
	FMOD::Sound* newSound = nullptr;
	m_pSystem->createSound ( filename.c_str ( ) , FMOD_LOOP_OFF+mode , 0 , &newSound );
	
	Sounds* createsound = new Sounds; 
	createsound->GetData ( newSound , m_pSystem );
	createsound->ReturnMod ( ) = mode;
	if ( result != FMOD_OK ) {
		std::cerr << filename << std::endl;
	}

	return createsound;

}
void SoundManager::TagMute ( int mode, std::string filename ) {
	
	for ( auto& pair : Channel ) {
		FMOD::Channel* channel = pair.second->GetChannel ( );
		if ( channel && pair.second->ReturnMod()==mode ) {
			channel->stop ( );
		}
	}
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
	//std::cerr << Channel.size ( ) << std::endl;
}


inline void Sounds::playSound ( float volume )
{

	FMOD::Channel* newChannel = nullptr;
	result = m_pSystem->playSound ( Soundfile , 0 , false , &newChannel );
	Channel = newChannel;

	SetVolume ( volume );

}

void Sounds::PauseSound ( ) {

	if ( Channel != nullptr ) {
		bool isPaused;
		Channel->getPaused ( &isPaused );
		Channel->setPaused ( !isPaused ); // 현재 상태에 따라 재생/일시 정지 전환
	}
}


void Sounds::ReplaySound (float volume ) {
	bool isPlaying = false;
	Channel->isPlaying ( &isPlaying );  // 현재 재생 중인지 확인
	if ( isPlaying == false && Channel != nullptr ) {

		unsigned int position = 0;
		Channel->stop ( );
		Channel->setPosition ( position , FMOD_TIMEUNIT_MS ); // 위치를 처음으로 설정
		playSound ( volume );  // 사운드 재생
		//if ( !isPlaying ) {
		//	// 사운드가 끝났으므로 위치를 처음으로 설정
		//	
		//	Channel->setPosition ( position , FMOD_TIMEUNIT_MS ); // 위치를 처음으로 설정
		//	playSound ( );  // 사운드 재생
		//}
		//else {
		//	Channel->setPosition ( position , FMOD_TIMEUNIT_MS );
		//}
		Debugging::STRINPUT ( "if" );
	}
	else {
		playSound ( volume );
		Debugging::STRINPUT ( "else" );
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


