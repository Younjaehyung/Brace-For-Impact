#include "Debugging.h"
int Debugging::debuggingMod = 0;
int Debugging::count = 0;
void Debugging::InputMod ( )
{

	if ( input::GetKey ( eKeyCode::U ) ) {//mod off
		debuggingMod = 0;
		count = 0;
	}
	else if ( input::GetKey ( eKeyCode::I ) ) {//mod on :1 
		debuggingMod = 1;
	}
	else if ( input::GetKey ( eKeyCode::O ) ) {//mod on :2
		debuggingMod = 2;
	}
	else if ( input::GetKey ( eKeyCode::P ) ) {//pause
		debuggingMod = 3;
	}

	if ( debuggingMod && !count ) {
		std::cerr << "DebuggingMOD ON"<<std::endl;
		count++;
	}
}
