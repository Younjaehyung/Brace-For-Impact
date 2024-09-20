#include "input.h"

std::vector<input::Key>input::mKeys = {};
//static멤버변수 이므로 전역에서 초기화함.

int ASCII[(UINT)eKeyCode::End] = {

	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
'Z', 'X', 'C', 'V', 'B', 'N', 'M',VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP,'F','G','N','M',VK_F1,VK_F2,VK_F3,VK_F4,VK_SPACE, VK_ESCAPE,
'1','2','3','4','5','6',

};

void input::Initialize() {

	for (size_t i = 0; i < (UINT)eKeyCode::End; i++) {

		Key key = {};
		key.bPressed = false;
		key.state = eKeyState::None;
		key.keyCode = (eKeyCode)i;

		mKeys.push_back(key);
	}
}

void input::Update() {
	for (size_t i = 0; i < mKeys.size(); i++) {
		//눌렀는지
		if (GetAsyncKeyState(ASCII[i]) & 0x8000) {
			if (mKeys[i].bPressed == true) {
				mKeys[i].state = eKeyState::Pressed;
			}
			else {
				mKeys[i].state = eKeyState::Down;
			}
			mKeys[i].bPressed = true;
		}
		else {// 아닌지

			if (mKeys[i].bPressed == true) {
				mKeys[i].state = eKeyState::Up;
			}
			else {
				mKeys[i].state = eKeyState::None;
			}
			mKeys[i].bPressed = false;
		}
		
		
	}
}
