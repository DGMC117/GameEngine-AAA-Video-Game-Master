#pragma once
#include "Application.h"
#include "ModuleCamera.h"

class Command {
public:
	virtual void execute() = 0;
};

class CameraForwardCommand : public Command {
public:
	virtual void execute() { App->camera->MoveForward(); }
};

class CameraBackwardsCommand : public Command {
public:
	virtual void execute() { App->camera->MoveBackwards(); }
};

class CameraLeftCommand : public Command {
public:
	virtual void execute() { App->camera->MoveLeft(); }
};

class CameraRightCommand : public Command {
public:
	virtual void execute() { App->camera->MoveRight(); }
};

class CameraUpCommand : public Command {
public:
	virtual void execute() { App->camera->MoveUp(); }
};

class CameraDownCommand : public Command {
public:
	virtual void execute() { App->camera->MoveDown(); }
};

class CameraForwardFastCommand : public Command {
public:
	virtual void execute() { App->camera->MoveForwardFast(); }
};

class CameraBackwardsFastCommand : public Command {
public:
	virtual void execute() { App->camera->MoveBackwardsFast(); }
};

class CameraLeftFastCommand : public Command {
public:
	virtual void execute() { App->camera->MoveLeftFast(); }
};

class CameraRightFastCommand : public Command {
public:
	virtual void execute() { App->camera->MoveRightFast(); }
};

class CameraUpFastCommand : public Command {
public:
	virtual void execute() { App->camera->MoveUpFast(); }
};

class CameraDownFastCommand : public Command {
public:
	virtual void execute() { App->camera->MoveDownFast(); }
};

class CameraPitchClockwiseCommand : public Command {
public:
	virtual void execute() { App->camera->PitchClockwise(); }
};

class CameraPitchCounterClockwiseCommand : public Command {
public:
	virtual void execute() { App->camera->PitchCounterClockwise(); }
};

class CameraYawClockwiseCommand : public Command {
public:
	virtual void execute() { App->camera->YawClockwise(); }
};

class CameraYawCounterClockwiseCommand : public Command {
public:
	virtual void execute() { App->camera->YawCounterClockwise(); }
};

class CameraRollClockwiseCommand : public Command {
public:
	virtual void execute() { App->camera->RollClockwise(); }
};

class CameraRollCounterClockwiseCommand : public Command {
public:
	virtual void execute() { App->camera->RollCounterClockwise(); }
};

class CameraPitchClockwiseMouseCommand : public Command {
public:
	virtual void execute() { App->camera->PitchClockwiseMouse(); }
};

class CameraPitchCounterClockwiseMouseCommand : public Command {
public:
	virtual void execute() { App->camera->PitchCounterClockwiseMouse(); }
};

class CameraYawClockwiseMouseCommand : public Command {
public:
	virtual void execute() { App->camera->YawClockwiseMouse(); }
};

class CameraYawCounterClockwiseMouseCommand : public Command {
public:
	virtual void execute() { App->camera->YawCounterClockwiseMouse(); }
};