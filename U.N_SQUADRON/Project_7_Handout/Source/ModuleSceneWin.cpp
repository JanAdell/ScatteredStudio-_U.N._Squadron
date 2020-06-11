#include "ModuleSceneWin.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "ModuleAudio.h"
#include "ModuleHud.h"

ModuleSceneWin::ModuleSceneWin(bool startEnabled) : Module(startEnabled)
{
	screen = { 0,0,256,224 };
}

ModuleSceneWin::~ModuleSceneWin() {}

bool ModuleSceneWin::Start() {



	LOG("Loading Win Scene");

	bool ret = true;


	bgTexture = App->textures->Load("Assets/sprites/scenes/WinScreen.png");
	App->audio->PlayMusic("Assets/music/Build/music/win.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	if (bgTexture == nullptr) {
		ret = false;
	}

	return ret;
}

update_status ModuleSceneWin::Update() {
	update_status ret = update_status::UPDATE_CONTINUE;

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN){
		App->transition->FadeToBlack(this, (Module*)App->initialScreen, 60);
	}

	if (App->input->keys[SDL_SCANCODE_F7] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->loose, 90);
	}

	if (App->input->keys[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->initialScreen);
	}

	return ret;
}


// Update: draw background
update_status ModuleSceneWin::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool ModuleSceneWin::CleanUp() {
	bool ret = true;

	if (!App->textures->Unload(bgTexture)) {
		LOG("Start Screen -> Error unloading the texture.");
		ret = false;
	}

	App->audio->StopMusic();

	return ret;
}

