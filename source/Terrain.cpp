#include "Terrain.h"

Terrain::Terrain(int noOfRings)
{
    this->noOfRings = noOfRings;
    for(int i=0; i<noOfRings+1; i++)
    {
        planes.push_back(new RingObject());
    }
    startTesselatedSize = startScale/lod;
    ringMesh = new RingMesh();
    platformMesh = new PlatformMesh();

    int scale = startScale;
    int tessSize = startTesselatedSize;
    for(int i=0; i<noOfRings+1; i++)
    {
        planes[i]->scale = scale;
        planes[i]->tesselatedSize = tessSize;
        scale *= 2;
        tessSize *= 2;
    }    
}

Terrain::~Terrain()
{
    delete ringMesh;
    delete platformMesh;
}

void Terrain::reconfigure(int scale, int lod)
{
    this->lod = lod;
    startScale = scale;
    startTesselatedSize = startScale/lod;
    int tessSize = startTesselatedSize;
    for(int i=0; i<noOfRings+1; i++)
    {
        planes[i]->scale = scale;
        planes[i]->tesselatedSize = tessSize;
        scale = scale * 2;
        tessSize = tessSize * 2;
    }  
}

int Terrain::getStartScale()
{
    return startScale;
}

int Terrain::getLod()
{
    return lod;
}

void Terrain::update(Vec3& campos)
{
    distance[0] = campos[0] - planes[0]->position[0];
    distance[1] = campos[2] - planes[0]->position[1];
}

void Terrain::bindPlatformMesh()
{
    platformMesh->bind();
}
int Terrain::getPlatformMeshIndicesSize()
{
    return platformMesh->indicesSize();
}


void Terrain::bindRingMesh()
{
    ringMesh->bind();
}

int Terrain::getRingMeshIndicesSize()
{
    return ringMesh->indicesSize();
}


void Terrain::unbindMesh()
{
    glBindVertexArray(0);
}

RingObject* Terrain::getPlanes(int i)
{
    return planes[i];
}

int Terrain::getNoOfRings()
{
    return noOfRings;
}
 