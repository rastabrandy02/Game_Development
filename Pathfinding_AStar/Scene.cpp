#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "PathFinding.h"

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
	// L12b: Create walkability map on map loading
	if(app->map->Load("iso_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		
		if(app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	pathTex = app->tex->Load("Assets/maps/path2.png");
	originTex = app->tex->Load("Assets/maps/x.png");
	
	// Load music
	app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	iPoint p = app->render->ScreenToWorld(mouseX, mouseY);
	p = app->map->WorldToMap(p.x, p.y);

	if(app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if(originSelected == true)
		{
			app->pathfinding->CreatePath(origin, p);
			originSelected = false;
		}
		else
		{
			origin = p;
			originSelected = true;
		}
	}

	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	// L02: DONE 3: Request Load / Save when pressing L/S
	if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		app->SaveGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= 1;

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += 1;

	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= 1;

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += 1;

	//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more

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

	// L12b: Debug pathfinding
	app->input->GetMousePosition(mouseX, mouseY);
	iPoint p = app->render->ScreenToWorld(mouseX, mouseY);
	p = app->map->WorldToMap(p.x, p.y);
	p = app->map->MapToWorld(p.x, p.y);

	app->render->DrawTexture(pathTex, p.x, p.y);

	const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

	for(uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		app->render->DrawTexture(pathTex, pos.x, pos.y);
	}

	iPoint originScreen = app->map->MapToWorld(origin.x, origin.y);
	app->render->DrawTexture(originTex, originScreen.x, originScreen.y);

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
