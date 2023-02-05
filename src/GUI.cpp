#include "GUI.h"

//Constructor to create GUI
GUI::GUI()
{
    mapSettingsGUI.setup("Map Settings");
    mapSettingsGUI.add(seedGUI.setup("Seed",1,1,1000));
    mapSettingsGUI.add(mapWidthGUI.setup("Map Size", 300, 100, 500));
    mapSettingsGUI.add(tileSizeGUI.setup("Tile Size", 5, 1, 10));
    mapSettingsGUI.add(terrainStyleGUI.setup("Terrain Style", 1, 1, 5));
    mapSettingsGUI.add(drawStyleGUI.setup("Draw Style", 1, 1, 3));
    mapSettingsGUI.add(textureAmplifyGUI.setup("Texture Brighten", 1, 1, 10));
    noiseSettingsGUI.setup("Noise Settings");
    noiseSettingsGUI.add(octavesGUI.setup("Octaves", 5,1,10));
    noiseSettingsGUI.add(noiseScaleGUI.setup("Noise Scale", 1, .1, 2));
    noiseSettingsGUI.add(lacunarityGUI.setup("Lacunarity", 2, .1, 3));
    noiseSettingsGUI.add(persistanceGUI.setup("Persistance", 0.5, 0, 1));
    heightSettingsGUI.setup("Height Settings");
    heightSettingsGUI.add(maxHeightGUI.setup("Max Height", 25, 1, 100));
    heightSettingsGUI.add(flattenHeightGUI.setup("Flatten Height", 10, 1, 50));
    mapSettingsGUI.setPosition(20, 20);
    noiseSettingsGUI.setPosition(20, 160);
    heightSettingsGUI.setPosition(20, 260);
    setSettings();

}
//Draw GUI
void GUI::draw()
{
    mapSettingsGUI.draw();
    noiseSettingsGUI.draw();
    heightSettingsGUI.draw();
    colourPalleteGUI.draw();
    setSettings();
}

void GUI::setSettings()
{   
    settings.textureAmplify = textureAmplifyGUI;
    settings.terrainStyle = terrainStyleGUI;
    settings.drawStyle = drawStyleGUI;
    settings.seed = seedGUI;
    settings.tileSize = tileSizeGUI;
    //Map Size
    settings.mapWidth = mapWidthGUI;
    settings.mapHeight = mapWidthGUI;
    settings.octaves = octavesGUI;
    settings.noiseScale = noiseScaleGUI;
    settings.lacunarity = lacunarityGUI;
    settings.persistance = persistanceGUI;

    settings.maxHeight = maxHeightGUI;
    settings.flattenHeight = flattenHeightGUI;
    
}

