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
	static int Size ( );
	static float Peektimer ( UINT );
	static bool Checktimer ( UINT );
	static void Edittimer ( UINT ,float);
	static void Settimer (UINT,float );
	static void Killtimer ( UINT);
	static void Updatetimer (float );
	static void InitTimer ( UINT edit_id );
};

