#ifndef __MAP_H__
#define __MAP_H__

#include "Module.h"
#include "List.h"
#include "Point.h"

#include "PugiXml\src\pugixml.hpp"

// L03: TODO 2: Create a struct to hold information for a TileSet
// Ignore Wangsets and Tile Types for now, but we want the image!
struct TileSet
{
    //Tile set
    int firstgrid;
    SString name;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int tileCoutn;
    int columns;

    //Image
    int width;
    int height;
    SDL_Texture* texture;

};
//<tileset firstgid = "1" name = "Desert" tilewidth = "32" tileheight = "32" spacing = "1" margin = "1"
//    tilecount = "48" columns = "8">
//    <image source = "tmw_desert_spacing.png" width = "265" height = "199" / >
// L03: TODO 1: Create a struct needed to hold the information to Map node
struct MapData
{
    int width;
    int height;
    int tileWidth;
    int tileHeight;

    List <TileSet*> tileSets;
};

class Map : public Module
{
public:

    Map();

    // Destructor
    virtual ~Map();

    // Called before render is available
    bool Awake(pugi::xml_node& conf);

    // Called each loop iteration
    void Draw();

    // Called before quitting
    bool CleanUp();

    // Load new map
    bool Load(const char* path);

private:

    // L03: TODO 3: Implement LoadMap to load the map properties
	bool LoadMap(pugi::xml_node mapFile);

	// L03: TODO 4: Implement the LoadTileSet function to load the tileset
	bool LoadTileSet(pugi::xml_node mapFile);

	// L03: TODO 1: Declare a variable data of the struct MapData
    MapData mapData;

    SString folder;
    bool mapLoaded;
};

#endif // __MAP_H__