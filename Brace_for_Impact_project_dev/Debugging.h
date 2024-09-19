#pragma once
#include <iostream>;
#include "Time.h"
#include "input.h"
#include <ctime>
#include <vector>
class Debugging
{
public:
	static int& ReturnMod ( ) {
		return debuggingMod;
	}
	
	static void InputMod ( );
	static void STRPRINT ( ); 
	static void STRINPUT ( std::string str );
	static void STRDELETE ( std::string str );
	static HBRUSH NULLBRUSH;
	static HPEN redpen;
	static HPEN yellowpen;
	static HPEN bluepen;
	static HPEN whitepen;
	static HPEN blackpen;
private:
	static int debuggingMod;
	static int count;
	
	static float printtimer;
	static std::vector<std::string> DebuggingString;
};
