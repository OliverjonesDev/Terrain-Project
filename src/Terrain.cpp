#include "Terrain.h"
#include "GUI.H"

void Terrain::draw() {

    height = settings.mapHeight / settings.tileSize;
    width = settings.mapWidth / settings.tileSize;
    glShadeModel(GL_SMOOTH);
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    GenerateNoise();
    GenerateTerrainMesh();
    CalculateNormals();
    DrawTypes();
}


//Generates the triangle grid for a heightmap to be placed onto.
void Terrain::GenerateTerrainMesh()
{
    //make the points inside of the mesh.
    mesh.clear();
    for (int y = 0; y < height ; y++) {
        for (int x = 0; x < width ; x++){
            //Basically a list of points with vector values.
            //places the vector at the height map location.
            mesh.addVertex(ofPoint((x - width / 2) * settings.tileSize, (y - height /2) * settings.tileSize,heightMap.at(y).at(x)));
            //Add vertex colour aswell
            //mesh.addColor(ofFloatColor(0, 0, 255));
            mesh.addNormal(ofVec3f(0, 0, 0));
        }
    }
    for (int y = 0; y < height -1; y++) {
        for (int x = 0; x < width -1; x++) {
            mesh.addIndex(x + y * width);
            mesh.addIndex((x + 1) + y * width);
            mesh.addIndex(x + (y + 1) * width);

            mesh.addIndex((x + 1) + y * width);
            mesh.addIndex((x + 1) + (y+1) * width);
            mesh.addIndex(x+ (y + 1) * width);
        }
    }


    //Taken from the ofMesh openframeworks wiki.
    //
    ///Terrain Prototype 1
    /*
    //Applying base perlin noise to the mesh

    //Summary
    //First Attempt to add noise into the mesh. I got the noise working with this but I could not
    //get the detail I wanted. After struggling with this implementation im going to look at other methods
    //of applying noise and creating detail similar to terrain and mountains.

    ofVec3f newPos;
    int i = 0;
    float frequency,amplitude;
    ofSeedRandom(settings.seed);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            frequency = 1;
            amplitude = 1;
            for (int j = 0; j < settings.octaves; j++)
            {
                newPos = mesh.getVertex(i);
                float noiseX = x/ width / settings.noiseScale * frequency;
                float noiseY = y/ height / settings.noiseScale * frequency;
                newPos.z += ofNoise(ofMap(x, 0, width * frequency, 0, settings.noiseScale),
                   ofMap(y, 0, height * frequency, 0, settings.noiseScale));
                //newPos.z += ofNoise(noiseX-x, noiseY-y) * amplitude;
                newPos.z *= amplitude * settings.maxHeight;
                frequency *= settings.lacunarity;
                amplitude *= settings.persistance;
            }
            if (newPos.z < minNoiseZ) {
                minNoiseZ = newPos.z;
            }
            if (newPos.z > maxNoiseZ) {
                maxNoiseZ = newPos.z;
            }
            mesh.setVertex(i, newPos);

            i++;
        }
    }
    */
}
void Terrain::GenerateNoise()
{
    //If this is not in the code, it will error as we require a heightmap to generate terrain. This populates the heightmap, with empty values before the terrain is generated.
    float noiseX, noiseY, noiseZ;
    float frequency, amplitude;
    float maxHeightDistance = pow(0.5, 0.5); //center to corner: sqrt(0.5^2 + 0.5^2)
    //Create Heightmap Matrix for X and Y with Z values.
    heightMap.clear();
    for (int y = 0; y < 500; y++)
    {
        vector<float> row;
        for (int x = 0; x < 500; x++)
        {
            row.push_back(0);
        }
        heightMap.push_back(row);
    }
    //Height map is now initalised, This can be called when the tilemap size is changed to recreate this.
    //Optimisation will come later.

    ofSeedRandom(settings.seed);
    //offset values for each of the octaves
    vector<float> seedOffsetX, seedOffsetY;
    for (int i = 0; i < settings.octaves; i++)
    {
        //Seed for each layer of octaves
        seedOffsetX.push_back(ofRandom(255));
        seedOffsetY.push_back(ofRandom(255));
    }
    minNoiseZ = 1;
    maxNoiseZ = 0;
    //This method of generating noise that can be scaled to create realistic terrain was taken form Sebastian Lagues Video on procedural generation.
    //To use this method.
    //We create frequency, amplitude which are controlled by the current octave and the user input settings (lacunarity and persistance).
    //Lacunarity - increase of frequency of each octave.
    //Amplitude - decrease of ampltiude of each octave.
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            frequency = 1;
            amplitude = 1;
            noiseZ = 0;

            for (int i = 0; i < settings.octaves; i++) {
                noiseX = ((float)x - width / 2) / width / settings.noiseScale * frequency + seedOffsetX.at(i);
                noiseY = ((float)y - height / 2) / height / settings.noiseScale * frequency + seedOffsetY.at(i);
                noiseZ += ofNoise(noiseX, noiseY) * amplitude;
                frequency *= settings.lacunarity;
                amplitude *= settings.persistance;
            }

            if (noiseZ < minNoiseZ) {
                minNoiseZ = noiseZ;
            }
            if (noiseZ > maxNoiseZ) {
                maxNoiseZ = noiseZ;
            }

            heightMap.at(y).at(x) = noiseZ;
        }
    }
        
    //This can be used to control the 'types of terrain'
    //Adding a user input to control map style or map setting, means we can adjust these values to create different styles of terrain
    //such as archepelogos, continent style, mountains etc.
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (settings.terrainStyle == 1)
            {
                //Normal
                heightMap.at(y).at(x) = pow(ofMap(heightMap.at(y).at(x), minNoiseZ, maxNoiseZ, 0, 1), settings.flattenHeight);
            }
            else if (settings.terrainStyle == 2) {

                //Lakes style
                float heightDistance = pow(pow((float)x / width - 0.5, 2) + pow((float)y / height - 0.5, 2), 0.5);
                heightMap.at(y).at(x) = ofMap(heightMap.at(y).at(x), minNoiseZ, maxNoiseZ, 0, 1);
                heightMap.at(y).at(x) = pow((heightMap.at(y).at(x) + maxHeightDistance / maxHeightDistance) / 2, settings.flattenHeight);
            }
            else if (settings.terrainStyle == 3) {

                //Crater style
                float heightDistance = pow(pow((float)x / width - 0.5, 2) + pow((float)y / height - 0.5, 2), 0.5);
                heightMap.at(y).at(x) = ofMap(heightMap.at(y).at(x), minNoiseZ, maxNoiseZ, 0, 1);
                heightMap.at(y).at(x) = pow((heightMap.at(y).at(x) + heightDistance / maxHeightDistance) / 2, settings.flattenHeight);
            }
            else if (settings.terrainStyle == 4) {
                //Singular Island
                float heightDistance = pow(pow((float)x / height - 0.5, 2) + pow((float)y / width - 0.5, 2), 0.5);
                heightMap.at(y).at(x) = ofMap(heightMap.at(y).at(x), minNoiseZ, maxNoiseZ, 0, 1);
                heightMap.at(y).at(x) = pow((heightMap.at(y).at(x) - heightDistance / maxHeightDistance + 1) / 2, settings.flattenHeight);
            }
            
            heightMap.at(y).at(x) = ofMap(heightMap.at(y).at(x), 0, 1, 0, settings.maxHeight);
        }
    }
    GenerateTexture();
}
        

void Terrain::CalculateNormals() {
    for (int i = 0; i < mesh.getIndices().size(); i += 3) {

        int p1 = mesh.getIndices()[i];
        int p2 = mesh.getIndices()[i + 1];
        int p3 = mesh.getIndices()[i + 2];
    
        ofVec3f v1 = mesh.getVertices()[p1] - mesh.getVertices()[p2];
        ofVec3f v2 = mesh.getVertices()[p3] - mesh.getVertices()[p2];
        ofVec3f crossProduct = v2.cross(v1);
        //We added the normals when we made the vertex so we do not need to add new normals
        //Adding normals to each vertex of the triangle.
        mesh.getNormals()[p1] += crossProduct;
        mesh.getNormals()[p2] += crossProduct;
        mesh.getNormals()[p3] += crossProduct;
    }
    //Calculating surface normals
    //Source - https://www.khronos.org/opengl/wiki/Calculating_a_Surface_Normal
    //Thought OPENGL being a big rendering pipeline would have wiki pages on how to do this.
}

void Terrain::GenerateTexture()
{
    texture.allocate(width, height, OF_IMAGE_COLOR);
    for (int y = 0; y < width; y ++)
    {
        for (int x = 0; x < height; x++)
        {
            ofColor colour(heightMap.at(x).at(y)  *settings.textureAmplify );
            texture.setColor(x, y, colour);
        }
    }
    texture.rotate90(-1);
    if (settings.tileSize != 1)
        texture.resize(settings.tileSize * width, settings.tileSize * height);
    texture.update();
}

void Terrain::DrawTypes()
{
    if (settings.drawStyle == 1)
    {
        mesh.drawFaces();
    }
    else if (settings.drawStyle == 2) {
        mesh.drawVertices();
    }
    else
    {
        mesh.drawWireframe();
    }
}



void Terrain::setup(GUI::settingsStruct s)
{
    settings = s;
}

