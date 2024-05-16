#pragma once
#include <Windows.h>
#include "Timer.h"
#include <iostream>
class Time
{
public:
	static void Initailize ( );//Time 초기화용 Update()
	static void Update ( );//deltatime 갱신용 Update()
	static void Render ( HDC hdc );//화면 프레임 체크용 Render()
	static float DeltaTime ( ) { return DeltaTimeValue; }//Deltatime값 출력용 DeltaTime()
	
private:
	static LARGE_INTEGER CpuFrequency;
	static LARGE_INTEGER PrevFrequency;
	static LARGE_INTEGER CurrentFrequency;
	static float DeltaTimeValue;

};
