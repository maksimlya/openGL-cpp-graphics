#include "TerrainTexturePack.h"

TerrainTexturePack::TerrainTexturePack(TerrainTexture backgroundTexture, TerrainTexture rTexture, TerrainTexture gTexture, TerrainTexture bTexture)
{
	this->backgroundTexture = backgroundTexture;
	this->rTexture = rTexture;
	this->gTexture = gTexture;
	this->bTexture = bTexture;
}

TerrainTexture TerrainTexturePack::getBackgroundTexture()
{
	return this->backgroundTexture;
}

TerrainTexture TerrainTexturePack::getRTexture()
{
	return this->rTexture;
}

TerrainTexture TerrainTexturePack::getGTexture()
{
	return this->gTexture;
}

TerrainTexture TerrainTexturePack::getBTexture()
{
	return this->bTexture;
}
