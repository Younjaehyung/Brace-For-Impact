#include "TankController.h"
bool TankController::tankmove = {};
bool TankController::tankaiming = {};
Frame TankController::Stage_frame = {};
Frame TankController::Title_frame = {};
Frame TankController::Cannon_frame = {};
int TankController::tankhp = {300};
int TankController::tankoil = {300};
float TankController::tankoilcount = {};
RECT TankController::camera = {};