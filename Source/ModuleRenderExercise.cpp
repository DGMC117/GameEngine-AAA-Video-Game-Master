#include "Globals.h"
#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"
#include "glew.h"
#include "MathGeoLib.h"
#include "ModuleCamera.h"
#include "ModuleTexture.h"

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
		-0.5f, 1.0f, 0.0f,
		 0.5f, 1.0f, 0.0f,
		-0.5f, 2.0f, 0.0f,
		 0.5f, 2.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f
	};
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

	// Create and Link Program
	program = App->program->CreateProgram(
		App->program->CompileShader(GL_VERTEX_SHADER, App->program->LoadShaderSource(".\\..\\Source\\default_vertex.glsl")),
		App->program->CompileShader(GL_FRAGMENT_SHADER, App->program->LoadShaderSource(".\\..\\Source\\default_fragment.glsl")));

	// Load Baboon Texture
	if (!App->texture->LoadTexture(BABOON_TEX_PATH, &tex_metadata, texture)) {
		LOG("Texture Failed To Load"); return false;
	}
	glGenTextures(1, &texture_gl);
	glBindTexture(GL_TEXTURE_2D, texture_gl);
	int internalFormat, format, type;
	switch (tex_metadata.format){
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
		case DXGI_FORMAT_R8G8B8A8_UNORM:
			internalFormat = GL_RGBA8;
			format = GL_RGBA;
			type = GL_UNSIGNED_BYTE;
			break;
		case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
		case DXGI_FORMAT_B8G8R8A8_UNORM:
			internalFormat = GL_RGBA8;
			format = GL_BGRA;
			type = GL_UNSIGNED_BYTE;
			break;
		case DXGI_FORMAT_B5G6R5_UNORM:
			internalFormat = GL_RGB8;
			format = GL_BGR;
			type = GL_UNSIGNED_BYTE;
			break;
		default:
			assert(false && "Unsupported format");
	}
	ScratchImage img;
	FlipRotate(texture.GetImages(), texture.GetImageCount(), texture.GetMetadata(), TEX_FR_FLIP_VERTICAL, img);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, tex_metadata.width, tex_metadata.height, 0, format, type, img.GetImage(0,0,0)->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

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

	// Texture
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * 4));
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, texture_gl);
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

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
	glDeleteTextures(1, &texture_gl);

	return true;
}