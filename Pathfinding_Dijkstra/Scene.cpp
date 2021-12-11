#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	// L03: DONE: Load map
	app->map->Load("iso_walk.tmx");
	
	// Load music
	app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	// L02: DONE 3: Request Load / Save when pressing L/S
	if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) app->LoadGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)	app->SaveGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) app->render->camera.y -= 1;

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) app->render->camera.y += 1;

	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) app->render->camera.x -= 1;

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) app->render->camera.x += 1;

	// Pathfinding testing inputs
	if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)	app->map->ResetPath();

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)	app->map->PropagateBFS();

	if (app->input->GetKey(SDL_SCANCODE_M) == KEY_REPEAT) app->map->PropagateBFS();

	if (app->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN) app->map->PropagateDijkstra();

	if (app->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT) app->map->PropagateDijkstra();

	if (app->input->GetMouseButtonDown(1) == KEY_DOWN)
	{
		iPoint p;
		app->input->GetMousePosition(p.x, p.y);
		app->map->ComputePath(p.x - app->render->camera.x, p.y - app->render->camera.y);
	}

	// Draw map
	app->map->Draw();

	// L03: DONE 7: Set the window title with map/tileset info
	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	iPoint mouseTile = app->map->WorldToMap(mouseX - app->render->camera.x, mouseY - app->render->camera.y);

	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:[%d,%d]",
				   app->map->data.width, app->map->data.height,
				   app->map->data.tileWidth, app->map->data.tileHeight,
				   app->map->data.tilesets.Count(), mouseTile.x, mouseTile.y);

	app->win->SetTitle(title.GetString());

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
