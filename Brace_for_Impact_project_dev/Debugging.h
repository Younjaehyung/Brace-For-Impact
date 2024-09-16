#pragma once
#include <iostream>;
#include "input.h"
class Debugging
{
public:
	static int& ReturnMod ( ) {
		return debuggingMod;
	}
	
	static void InputMod ( );

private:
	static int debuggingMod;
	
};
