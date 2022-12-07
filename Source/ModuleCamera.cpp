#include "ModuleCamera.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleCamera::ModuleCamera() {}

ModuleCamera::~ModuleCamera() {}

bool ModuleCamera::Init() {
	camera_move_speed = 2.0f;
	camera_rotate_speed = 35.0f;

	hori_fov = 90.0f;

	frustum.type = FrustumType::PerspectiveFrustum;
	SetPlaneDistances(0.1f, 100.0f);
	SetFOV();
	SetPosition(float3(0.0f, 0.0f, 5.0f));
	float3 target = float3(0.0f, 0.0f, 0.0f);
	LookAt(target);

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

float4x4 ModuleCamera::LookAt(float3 &target) {
	float3 forward = target - frustum.pos;
	forward.Normalize();
	float3 up = float3::unitY;
	float3 right = Cross(forward, up);
	right.Normalize();
	up = Cross(right, forward);
	up.Normalize();

	float4x4 res;
	res[0][0] = right.x; res[0][1] = up.x; res[0][2] = -forward.x; res[0][3] = frustum.pos.x;
	res[1][0] = right.y; res[1][1] = up.y; res[1][2] = -forward.y; res[1][3] = frustum.pos.y;
	res[2][0] = right.z; res[2][1] = up.z; res[2][2] = -forward.z; res[2][3] = frustum.pos.z;
	res[3][0] = 0.0f;	 res[3][1] = 0.0f; res[3][2] = 0.0f;	   res[3][3] = 1.0f;

	// Trying with frustum
	frustum.front = forward;
	frustum.up = up;

	return res;
}

float4x4 ModuleCamera::GetViewMatrix() {
	float4x4 res = float4x4(frustum.ViewMatrix());
	return res;
}

float4x4 ModuleCamera::GetProjectionMatrix() {
	return frustum.ProjectionMatrix();
}

void ModuleCamera::MoveForward() {
	float3 translation = float3(0.0f, 0.0f, App->delta_time * camera_move_speed);
	TranslateCamera(translation);
}

void ModuleCamera::MoveBackwards() {
	float3 translation = float3(0.0f, 0.0f, App->delta_time * -camera_move_speed);
	TranslateCamera(translation);
}

void ModuleCamera::MoveLeft() {
	float3 translation = float3(App->delta_time * -camera_move_speed, 0.0f, 0.0f);
	TranslateCamera(translation);
}

void ModuleCamera::MoveRight() {
	float3 translation = float3(App->delta_time * camera_move_speed, 0.0f, 0.0f);
	TranslateCamera(translation);
}

void ModuleCamera::MoveUp() {
	float3 translation = float3(0.0f, App->delta_time * camera_move_speed, 0.0f);
	TranslateCamera(translation);
}

void ModuleCamera::MoveDown() {
	float3 translation = float3(0.0f, App->delta_time * -camera_move_speed, 0.0f);
	TranslateCamera(translation);
}

void ModuleCamera::MoveForwardFast() {
	float3 translation = float3(0.0f, 0.0f, App->delta_time * camera_move_speed * 3);
	TranslateCamera(translation);
}

void ModuleCamera::MoveBackwardsFast() {
	float3 translation = float3(0.0f, 0.0f, App->delta_time * -camera_move_speed * 3);
	TranslateCamera(translation);
}

void ModuleCamera::MoveLeftFast() {
	float3 translation = float3(App->delta_time * -camera_move_speed * 3, 0.0f, 0.0f);
	TranslateCamera(translation);
}

void ModuleCamera::MoveRightFast() {
	float3 translation = float3(App->delta_time * camera_move_speed * 3, 0.0f, 0.0f);
	TranslateCamera(translation);
}

void ModuleCamera::MoveUpFast() {
	float3 translation = float3(0.0f, App->delta_time * camera_move_speed * 3, 0.0f);
	TranslateCamera(translation);
}

void ModuleCamera::MoveDownFast() {
	float3 translation = float3(0.0f, App->delta_time * -camera_move_speed * 3, 0.0f);
	TranslateCamera(translation);
}

void ModuleCamera::PitchClockwise() {
	float3 rot = float3(App->delta_time * -camera_rotate_speed, 0.0f, 0.0f);
	RotateCamera(rot);
}

void ModuleCamera::PitchCounterClockwise() {
	float3 rot = float3(App->delta_time * camera_rotate_speed, 0.0f, 0.0f);
	RotateCamera(rot);
}

void ModuleCamera::YawClockwise() {
	float3 rot = float3(0.0f, App->delta_time * -camera_rotate_speed, 0.0f);
	RotateCamera(rot);
}

void ModuleCamera::YawCounterClockwise() {
	float3 rot = float3(0.0f, App->delta_time * camera_rotate_speed, 0.0f);
	RotateCamera(rot);
}

void ModuleCamera::RollClockwise() {
	float3 rot = float3(0.0f, 0.0f, App->delta_time * -camera_rotate_speed);
	RotateCamera(rot);
}

void ModuleCamera::RollCounterClockwise() {
	float3 rot = float3(0.0f, 0.0f, App->delta_time * camera_rotate_speed);
	RotateCamera(rot);
}

void ModuleCamera::RotateCamera(float3& rotation_degs) {
	float3x3 rotation_matrix =
		float3x3::RotateAxisAngle(frustum.WorldRight(), DegToRad(rotation_degs.x))
		* float3x3::RotateAxisAngle(frustum.up, DegToRad(rotation_degs.y))
		* float3x3::RotateAxisAngle(frustum.front, DegToRad(rotation_degs.z));

	frustum.front = rotation_matrix.MulDir(frustum.front);
	frustum.front.Normalize();
	frustum.up = rotation_matrix.MulDir(frustum.up);
	frustum.up.Normalize();
}

void ModuleCamera::TranslateCamera(float3& translation) {
	frustum.pos += frustum.WorldRight() * translation.x;
	frustum.pos += float3(0.0f, 1.0f, 0.0f) * translation.y;
	frustum.pos += frustum.front * translation.z;
}