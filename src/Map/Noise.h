#pragma once

#include <vector>
#include "Vector2.h"

class Noise
{
public:
	Noise(unsigned int num_tiles_y, unsigned int num_tiles_x);

	float PerlinFunction(float x, float y);

	void printNoise() const;

	inline std::vector< std::vector<float> > NoiseArray() { return m_NoiseArray; }

private:
	// Represent the dimensions of the 2D grid in units of tiles
	unsigned int NUM_TILES_Y;
	unsigned int NUM_TILES_X;

	// 2-Dimensional Grid of random, unit-length gradient vectors that will be used in Perlin function
	std::vector< std::vector<Vector2> > m_Grid;
	// (x, y) points in 2D grid at which Perlin noise value will be computed
	std::vector< std::vector<Vector2> > m_Indexes;
	// 2D array of raw noise generated by Perlin Function 
	std::vector< std::vector<float> > m_NoiseArray;

	// Routines that will be used in the main Perlin function
	float dotProduct(float gridx, float gridy, float x, float y);
	Vector2 computeOffsetVector(float gridx, float gridy, float x, float y);
	float linearInterpolation(float n0, float n1, float weight);
	float fadeFunction(float preFade);
}; 
