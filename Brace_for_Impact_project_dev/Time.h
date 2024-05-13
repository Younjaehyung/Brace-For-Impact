#pragma once
#include <Windows.h>

class Time
{
public:
	static void Initailize ( );
	static void Update ( );
	static void Render ( HDC hdc );

	static float DeltaTime ( ) { return DeltaTimeValue; }

private:
	static LARGE_INTEGER CpuFrequency;
	static LARGE_INTEGER PrevFrequency;
	static LARGE_INTEGER CurrentFrequency;
	static float DeltaTimeValue;
};
