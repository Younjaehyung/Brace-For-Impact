#include "Time.h"

LARGE_INTEGER Time::CpuFrequency = {};
LARGE_INTEGER Time::PrevFrequency = {};
LARGE_INTEGER Time::CurrentFrequency = {};
float Time::DeltaTimeValue = 0.0f;

void Time::Initailize ( )	//Time 초기화용 Update()
{
	// Cpu 고유 진동수
	QueryPerformanceFrequency ( &CpuFrequency );

	// 프로그램이 시작 했을 때 현재 진동수
	QueryPerformanceCounter ( &PrevFrequency );
}

void Time::Update ( )	//deltatime 갱신용 Update()
{
	QueryPerformanceCounter ( &CurrentFrequency );

	float differenceFrequency
		= static_cast< float >( CurrentFrequency.QuadPart - PrevFrequency.QuadPart );
	DeltaTimeValue = differenceFrequency / static_cast< float >( CpuFrequency.QuadPart );
	PrevFrequency.QuadPart = CurrentFrequency.QuadPart;

	Timer::Updatetimer ( DeltaTime ( ) );
}

void Time::Render ( HDC hdc )	//화면 프레임 체크용 Render()
{

	static float time = 0.0f;
	

	float fps = 1.0f / DeltaTimeValue;

	wchar_t str[ 50 ] = L"";


	if ( fps < 100 ) {	//100 fps 이하시 콘솔창 출력
	//	std::cout<<"time" << (int)fps << std::endl;
	}
	
	wsprintf ( str , L"fps : %d" , (int)fps );
		
	
	int len = wcsnlen_s ( str , 50 );
	
//	TextOut ( hdc , 10 , 900 , str , len );


}