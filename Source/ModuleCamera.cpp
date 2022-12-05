#include "ModuleCamera.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleCamera::ModuleCamera() {}

ModuleCamera::~ModuleCamera() {}

bool ModuleCamera::Init() {
	camera_pos = float3(2.0f, 3.0f, 5.0f);
	camera_translation = float3::zero;
	camera_rotation = float3::zero;
	camera_abs_translation = float3::zero;

	frustum.type = FrustumType::PerspectiveFrustum;
	SetPosition(float3::zero);
	SetOrientation(-float3::unitZ, float3::unitY);
	SetPlaneDistances(0.1f, 100.0f);
	hori_fov = 90.0f;
	SetFOV();
	return true;
}

update_status ModuleCamera::PreUpdate() {
	return UPDATE_CONTINUE;
}

update_status ModuleCamera::Update() {
	return UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate() {
	return UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp() {
	return true;
}

void ModuleCamera::SetFOV() {
	frustum.horizontalFov = DegToRad(hori_fov);
	frustum.verticalFov = frustum.horizontalFov / ((float)App->window->GetResolutionWidth() / (float)App->window->GetResolutionHeight());
}

void ModuleCamera::SetPlaneDistances(float near_dist, float far_dist) {
	frustum.nearPlaneDistance = near_dist;
	frustum.farPlaneDistance = far_dist;
}

void ModuleCamera::SetPosition(const float3 &pos) {
	frustum.pos = pos;
}

void ModuleCamera::SetOrientation(const float3 &front, const float3 &up) {
	frustum.front = front;
	frustum.up = up;
}

float4x4 ModuleCamera::LookAt(float3 target) {
	float3 forward = target - camera_pos;
	forward.Normalize();
	float3 up = float3::unitY;
	float3 right = Cross(forward, up);
	right.Normalize();
	up = Cross(right, forward);
	up.Normalize();

	float4x4 res;
	res[0][0] = right.x; res[0][1] = up.x; res[0][2] = -forward.x; res[0][3] = camera_pos.x;
	res[1][0] = right.y; res[1][1] = up.y; res[1][2] = -forward.y; res[1][3] = camera_pos.y;
	res[2][0] = right.z; res[2][1] = up.z; res[2][2] = -forward.z; res[2][3] = camera_pos.z;
	res[3][0] = 0.0f;	 res[3][1] = 0.0f; res[3][2] = 0.0f;	   res[3][3] = 1.0f;
	return res;
}

float4x4 ModuleCamera::GetViewMatrix() {
	float3x3 rotation_matrix = 
		float3x3::RotateAxisAngle(float3::unitX, DegToRad(camera_rotation.x))
		* float3x3::RotateAxisAngle(float3::unitY, DegToRad(camera_rotation.y))
		* float3x3::RotateAxisAngle(float3::unitZ, DegToRad(camera_rotation.z));

	float4x4 res = LookAt(float3(0.0f, 0.0f, 0.0f));
	float4x4 transform_matrix = float4x4(rotation_matrix);
	transform_matrix[0][3] += camera_abs_translation.x;
	transform_matrix[1][3] += camera_abs_translation.y;
	transform_matrix[2][3] += camera_abs_translation.z;
	res = transform_matrix * res;
	res.Inverse();
	transform_matrix = float4x4::identity;
	transform_matrix[0][3] = camera_translation.x;
	transform_matrix[1][3] = camera_translation.y;
	transform_matrix[2][3] = camera_translation.z;
	res = transform_matrix * res;
	return res;
}

float4x4 ModuleCamera::GetProjectionMatrix() {
	return frustum.ProjectionMatrix();
}

void ModuleCamera::TranslateForward(float unit) {
	camera_translation.z += unit;
}
void ModuleCamera::TranslateSide(float unit) {
	camera_translation.x += unit;
}
void ModuleCamera::TranslateVerticalAbs(float unit) {
	camera_abs_translation.y += unit;
}
void ModuleCamera::Pitch(float unit) {
	camera_rotation.x += unit;
}
void ModuleCamera::Yaw(float unit) {
	camera_rotation.y += unit;
}