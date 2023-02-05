#pragma once
#include "ofMain.h"
#include "ofxGui.h"
class GUI
{

public :
    GUI();
    //Using a struct as its very easy to read from through other cpp files.
    //just reference the struct and read the values
    struct settingsStruct
    {
        int seed, tileSize, mapWidth, mapHeight, octaves;
        float noiseScale, lacunarity, persistance;
        int maxHeight, flattenHeight;
        int terrainStyle, drawStyle, textureAmplify;
        int oceanHeight, coastalHeight, beachHeight, valleyHeight, forestHeight, hillHeight, snowyHillHeight, mountainHeight;
        ofColor oceanColour, coastColour, beachColour, valleyColour, forestColour, hillColour, snowyHillColour, mountainColour;
    };
    settingsStruct settings;
    void draw();
private:
    //Panel variables
    ofxPanel mapSettingsGUI,noiseSettingsGUI,heightSettingsGUI,
    colourPalleteGUI;

    //Map Settings
    ofxIntSlider mapWidthGUI, mapHeightGUI;
    ofxIntSlider tileSizeGUI, seedGUI, terrainStyleGUI, drawStyleGUI, textureAmplifyGUI;
    
    //Noise Settings
    ofxIntSlider octavesGUI;
    //Noise Settings
    ofxFloatSlider noiseScaleGUI,lacunarityGUI,persistanceGUI;

    //Height Settings
    ofxIntSlider maxHeightGUI, flattenHeightGUI;

    void setSettings();
    
    
};
