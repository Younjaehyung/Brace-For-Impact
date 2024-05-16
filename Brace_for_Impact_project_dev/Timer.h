#pragma once
#include <Windows.h>
#include <vector>


class Timer
{
	typedef struct timer_ID {
		UINT ID;
		float time;
		float want_time;

	}timer_ID;
private:
	static std::vector<timer_ID> timerID;
public:
	static int Size ( );	//현재 타이머의 개수 확인
	static float Peektimer ( UINT );	//현재 확인할 타이머의 경과 시간 확인, ID : 확인할 타이머의 ID
	static bool Checktimer ( UINT );	//확인할 타이머의 시간이 설정한 시간이 지나면 true를 반환 check_id : 확인할 타이머의 ID
	static void Edittimer ( UINT ,float);	//수정하고 싶은 타이머의 기본 초설정을 강제로 변경, edit_id : 수정하고 싶은 ID, want_time : 수정할 시간
	static void Settimer (UINT,float );	//timer 생성, create_id : 생성할 timer의 ID, settingtimer : 초 설정
	static void Killtimer ( UINT);	//타이머 삭제, delete_id : 삭제 하고 싶은 타이머의 ID
	static void Updatetimer (float );	//타이머 update	<<건들지 마시오>>
	static void InitTimer ( UINT edit_id );	//경과 시간 강제 초기화, edit_id : 해당 ID를 가진 타이머의 경과시간 강제 초기화
	static void Deletetimer ( );	//모든 타이머 삭제

};

