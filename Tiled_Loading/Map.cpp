
#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

#include <math.h>
#include "SDL_image/include/SDL_image.h"

Map::Map() : Module(), mapLoaded(false)
{
    name.Create("map");
}

// Destructor
Map::~Map()
{}

// Called before render is available
bool Map::Awake(pugi::xml_node& config)
{
    LOG("Loading Map Parser");
    bool ret = true;

    folder.Create(config.child("folder").child_value());

    return ret;
}

void Map::Draw()
{
    if (mapLoaded == false)
  
        return;

    ListItem<TileSet*>* item;
    item = mapData.tileSets.start;

    while (item != NULL)
    {
        app->render->DrawTexture(item->data->texture, 0, 0);
        item = item->next;
    }

    // L03: TODO 6: Iterate all tilesets and draw all their 
    // images in 0,0 (you should have only one tileset for now)

}

// Called before quitting
bool Map::CleanUp()
{
    LOG("Unloading map");

    // L03: TODO 2: Make sure you clean up any memory allocated from tilesets/map

    return true;
}

// Load new map
bool Map::Load(const char* filename)
{
    bool ret = true;
    SString tmp("%s%s", folder.GetString(), filename);

    pugi::xml_document mapFile;
    pugi::xml_parse_result result = mapFile.load_file(tmp.GetString());

    if(result == NULL)
    {
        LOG("Could not load map xml file %s. pugi error: %s", filename, result.description());
        ret = false;
    }

    if(ret == true)
    {
        ret = LoadMap(mapFile.child("map"));
    }

    if (ret == true)
    {
        ret = LoadTileSet(mapFile);
    }

    if(ret == true)
    {
        //L03: TODO 5: LOG all the data loaded iterate all tilesets and LOG everything
        LOG("I loaded my map %i x %i: ",mapData.width, mapData.height);
        ListItem<TileSet*>* item;
        item = mapData.tileSets.start;

        //LOG info about the tile sets
        while (item != NULL)
        {
            LOG("Firstgrid: %i", item->data->firstgrid);
                item = item->next;
        }
    }

    if(mapFile) mapFile.reset();

    mapLoaded = ret;

    return ret;
}

// L03: TODO 3: Implement LoadMap to load the map properties
bool Map::LoadMap(pugi::xml_node mapFile)
{
    mapData.width = mapFile.attribute("width").as_int();
    mapData.height = mapFile.attribute("height").as_int();
    mapData.tileWidth = mapFile.attribute("tilewidth").as_int();
    
    bool ret = true;

    return ret;
}

// L03: TODO 4: Implement the LoadTileSet function to load the tileset properties
bool Map::LoadTileSet(pugi::xml_node mapFile)
{
    bool ret = true; 
    for (pugi::xml_node tileset = mapFile.child("map").child("tileset"); tileset; tileset = tileset.next_sibling("tileset"))
    {
        TileSet* tilesetElem = new TileSet();
        tilesetElem->firstgrid = tileset.attribute("firstgrid").as_int();

        SString tmp("%s%s", folder.GetString(), tileset.child("image").attribute("source"));
        tilesetElem->texture = app->tex->Load(tmp.GetString());

        mapData.tileSets.add(tilesetElem);
    }
    return ret;
}


