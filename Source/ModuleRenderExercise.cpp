#include "Globals.h"
#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"
#include "glew.h"
#include "MathGeoLib.h"
#include "ModuleCamera.h"

ModuleRenderExercise::ModuleRenderExercise()
{
}

// Destructor
ModuleRenderExercise::~ModuleRenderExercise()
{
}

// Called before render is available
bool ModuleRenderExercise::Init()
{
	LOG("Initializing Render Exercise Module");

	// Create VBO
	float vtx_data[] = { 
		-1.0f, -1.0f, 0.0f, 
		 1.0f, -1.0f, 0.0f, 
		 0.0f,  1.0f, 0.0f 
	};
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

	// Create and Link Program
	program = App->program->CreateProgram(
		App->program->CompileShader(GL_VERTEX_SHADER, App->program->LoadShaderSource(".\\..\\Source\\default_vertex.glsl")),
		App->program->CompileShader(GL_FRAGMENT_SHADER, App->program->LoadShaderSource(".\\..\\Source\\default_fragment.glsl")));

	return true;
}

update_status ModuleRenderExercise::PreUpdate()
{
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRenderExercise::Update()
{
	// Select Shaders
	glUseProgram(program);
	// Retrieve Transformation Matrices
	float4x4 model, view, proj;
	model = float4x4::identity;
	view = App->camera->GetViewMatrix();
	proj = App->camera->GetProjectionMatrix();
	glUniformMatrix4fv(0, 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(1, 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(2, 1, GL_TRUE, &proj[0][0]);

	// Object Binding and Drawing
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	// 1 triangle to draw = 3 vertices
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::PostUpdate()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderExercise::CleanUp()
{
	glDeleteBuffers(1, &vbo);
	glDeleteProgram(program);

	return true;
}