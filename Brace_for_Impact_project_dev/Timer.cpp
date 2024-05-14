#include "Timer.h"

std::vector<Timer::timer_ID>Timer::timerID = {};
void Timer::Settimer (  UINT create_id , float settigtimer) {
	timer_ID temp;
	temp.ID = create_id;
	temp.time = 0;
	temp.want_time = settigtimer;
	timerID.push_back (temp);
}

float Timer::Peektimer ( UINT id ) {

	for ( int i = 0; i < timerID.size ( ); i++ ) {
		if ( timerID[ i ].ID == id ) {
			
				return timerID[i].time;
			
			
		}

	}
}

int Timer::Size ( ) {
	return timerID.size ( );
}

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

void Timer::Edittimer ( UINT edit_id,float want_time ) {

	for ( int i = 0; i < timerID.size ( ); i++ ) {
		if ( timerID[ i ].ID == edit_id ) {

			timerID[ i ].want_time=want_time;

			break;
		}

	}
}

void Timer::InitTimer ( UINT edit_id  ) {
	for ( int i = 0; i < timerID.size ( ); i++ ) {
		if ( timerID[ i ].ID == edit_id ) {

			timerID[ i ].time = 0;

			return;
		}

	}
}

void Timer::Killtimer ( UINT delete_id ) {
	for ( int i = 0; i < timerID.size ( ); i++ ) {
		if ( timerID[ i ].ID == delete_id ) {
		timerID.erase ( timerID.begin ( ) + i );
		}

	}
}

void Timer::Updatetimer (float deltaTime) {
	for ( int i = 0; i < timerID.size ( ); i++ ) {
		timerID[ i ].time += deltaTime;
	}
}