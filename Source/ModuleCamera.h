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
	float4x4 LookAt(float3 target);
	float4x4 GetViewMatrix();
	float4x4 GetProjectionMatrix();
	float4x4 GetViewTransformMatrix();

private:
	Frustum frustum;
	float hori_fov;

	float3 camera_pos;
	float3 camera_translation;
	float3 camera_rotation;
	float3 camera_abs_translation;
};
