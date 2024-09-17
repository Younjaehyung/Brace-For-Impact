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
	

	static HBRUSH NULLBRUSH;
	static HPEN redpen;
	static HPEN yellowpen;
	static HPEN bluepen;
	static HPEN whitepen;
	static HPEN blackpen;
private:
	static int debuggingMod;
	static int count;
	
};
