#include "TankController.h"
bool TankController::tankmove = {};
bool TankController::tankaiming = {};
bool TankController::dash = {};
Frame TankController::Stage_frame = {};
Frame TankController::Cannon_frame = {};
int TankController::tankhp = {300};
int TankController::tankoil = {300};
int TankController::tankbullet = {0};
RECTS TankController::TankRect = {};
float TankController::tankoilcount = {};
RECT TankController::camera = {};