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