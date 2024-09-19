#include "Debugging.h"

int Debugging::debuggingMod = 0;
int Debugging::count = 0;
float Debugging::printtimer = 0;
std::vector<std::string> Debugging::DebuggingString = {};
HBRUSH Debugging::NULLBRUSH= ( HBRUSH ) GetStockObject ( NULL_BRUSH );
HPEN Debugging::redpen = CreatePen ( 1 , 1 , RGB ( 220 , 50 , 50 ) );

HPEN Debugging::yellowpen = CreatePen ( 1 , 1 , RGB ( 50 , 220 , 50 ) );

HPEN Debugging::bluepen = CreatePen ( 1 , 1 , RGB ( 50 , 50 , 220 ) );

HPEN Debugging::whitepen = CreatePen ( 1 , 1 , RGB ( 255 , 255 , 255 ) );

HPEN Debugging::blackpen = CreatePen ( 1 , 1 , RGB ( 0 ,0 , 0 ) );


void Debugging::InputMod ( )
{

	if ( input::GetKey ( eKeyCode::U ) ) {//mod off
		debuggingMod = 0;
		count = 0;
		printtimer = 0;
	}
	else if ( input::GetKey ( eKeyCode::I ) ) {//mod on :1 
		debuggingMod = 1;

	}
	else if ( input::GetKey ( eKeyCode::O ) ) {//mod on :2
		debuggingMod = 2;

	}
	else if ( input::GetKey ( eKeyCode::P ) ) {//pause
		if ( debuggingMod == 3 ) {
			debuggingMod = 1;
		}
		else {
			debuggingMod = 3;
		}
		
	}

	if ( debuggingMod && !count ) {
		std::cerr << "DebuggingMOD ON"<<std::endl;
		count++;

	}
}

void Debugging::STRPRINT ( )
{
	if ( printtimer >= 3 ) {
		
		
		std::cout << "============"<< printtimer <<"==================== = " << std::endl;

		
		for ( auto& i : DebuggingString ) {
			std::cerr << i << std::endl;
		}



		printtimer = 0;
	}





	printtimer += Time::DeltaTime ( );
}


void Debugging::STRINPUT (std::string str )
{
	DebuggingString.push_back ( str );
	
}

void Debugging::STRDELETE ( std::string str )
{
	for ( auto iter = DebuggingString.begin ( ); iter != DebuggingString.end ( ); iter++ ) {
		if ( *iter == str ) {
			DebuggingString.erase ( iter );
			return;
		}
	}
	
}
