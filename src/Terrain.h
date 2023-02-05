#pragma once

#include "ofMain.h"
#include "GUI.h"

class Terrain
{
public:
	void setup(GUI::settingsStruct s);
	void draw();
	vector<vector<float>> heightMap;
	float minNoiseZ, maxNoiseZ;
	ofImage texture;
private:
	void GenerateTerrainMesh();
	void GenerateNoise();
	void CalculateNormals();
	void GenerateTexture();
	void DrawTypes();
	ofMesh mesh;
	GUI::settingsStruct settings;
	vector<ofVec3f> vertices;
	vector<ofColor> colors;
	vector<ofIndexType> indices;
	float width, height;

};

