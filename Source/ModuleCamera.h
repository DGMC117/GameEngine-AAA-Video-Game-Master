#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib.h"

class ModuleCamera : public Module
{
public:
	ModuleCamera();
	~ModuleCamera();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void SetFOV();
	void SetPlaneDistances(float near_dist, float far_dist);
	void SetPosition(const float3 &pos);
	void SetOrientation(const float3 &front, const float3 &up);
	float4x4 LookAt(float3 &target);
	float4x4 GetViewMatrix();
	float4x4 GetProjectionMatrix();
	float4x4 GetViewTransformMatrix();

	void MoveForward();
	void MoveBackwards();
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void PitchClockwise();
	void PitchCounterClockwise();
	void YawClockwise();
	void YawCounterClockwise();

	void RotateCamera(float3& rotation_degs);
	void TranslateCamera(float3& translation);

private:
	Frustum frustum;
	float hori_fov;

	float camera_move_speed;
	float camera_rotate_speed;
};
