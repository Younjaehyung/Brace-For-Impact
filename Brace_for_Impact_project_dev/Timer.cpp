#include "Timer.h"
std::vector<Timer::timer_ID>Timer::timerID = {};



//timer 생성, create_id : 생성할 timer의 ID, settingtimer : 초 설정
void Timer::Settimer (  UINT Create_ID , float SettigTimer) {	
	timer_ID temp;
	temp.ID = Create_ID;
	temp.time = 0;
	temp.want_time = SettigTimer;
	timerID.push_back (temp);
}


//현재 확인할 타이머의 경과 시간 확인, ID : 확인할 타이머의 ID
float Timer::Peektimer ( UINT ID ) {

	for ( int i = 0; i < timerID.size ( ); i++ ) {
		if ( timerID[ i ].ID == ID ) {
			
				return timerID[i].time;
			
			
		}

	}
}

//현재 타이머의 개수 확인
int Timer::Size ( ) {
	return timerID.size ( );
}

//확인할 타이머의 시간이 설정한 시간이 지나면 true를 반환, check_id : 확인할 타이머의 ID
bool Timer::Checktimer ( UINT check_id ) {

	for ( int i = 0; i < timerID.size ( ); i++ ) {
		if ( timerID[ i ].ID == check_id ) {
			if ( timerID[ i ].want_time <= timerID[ i ].time ) {
				timerID[i ].time = 0;
				return true;
			}
			else {
				return false;
			}
		}	
		
	}
}

//수정하고 싶은 타이머의 기본 초설정을 강제로 변경, edit_id : 수정하고 싶은 ID, want_time : 수정할 시간
void Timer::Edittimer ( UINT edit_id,float want_time ) {

	for ( int i = 0; i < timerID.size ( ); i++ ) {
		if ( timerID[ i ].ID == edit_id ) {

			timerID[ i ].want_time=want_time;

			break;
		}

	}
}

//경과 시간 강제 초기화, edit_id : 해당 ID를 가진 타이머의 경과시간 강제 초기화
void Timer::InitTimer ( UINT edit_id  ) {
	for ( int i = 0; i < timerID.size ( ); i++ ) {
		if ( timerID[ i ].ID == edit_id ) {

			timerID[ i ].time = 0;

			return;
		}

	}
}

//타이머 삭제, delete_id : 삭제 하고 싶은 타이머의 ID
void Timer::Killtimer ( UINT delete_id ) {
	for ( int i = 0; i < timerID.size ( ); i++ ) {
		if ( timerID[ i ].ID == delete_id ) {
		timerID.erase ( timerID.begin ( ) + i );
		}

	}
}

//타이머 update			<<건들지 마시오>>
void Timer::Updatetimer (float deltaTime) {
	for ( int i = 0; i < timerID.size ( ); i++ ) {
		timerID[ i ].time += deltaTime;
	}
}

//모든 타이머 삭제
void Timer::Deletetimer ( ) {
	timerID.clear ( );
}
