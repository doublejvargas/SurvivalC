#pragma once

#include <vector>
#include "Vector2.h"

class Noise
{
public:
	Noise(unsigned int game_map_y, unsigned int game_map_x);

	float PerlinFunction(float y, float x);

	void printNoise() const;

	inline std::vector< std::vector<float> > noiseArray() { return m_NoiseArray; }

private:
	// Represent the dimensions of the 2D grid in units of tiles
	unsigned int GAME_MAP_Y;
	unsigned int GAME_MAP_X;

	// 2-Dimensional Grid of random, unit-length gradient vectors that will be used in Perlin function
	std::vector< std::vector<Vector2> > m_Grid;
	// (x, y) points in 2D grid at which Perlin noise value will be computed
	std::vector< std::vector<Vector2> > m_Indexes;
	// 2D array of raw noise generated by Perlin Function 
	std::vector< std::vector<float> > m_NoiseArray;

	// Routines that will be used in the main Perlin function
	float dotProduct(float gridy, float gridx, float y, float x);
	Vector2 computeOffsetVector(float gridy, float gridx, float y, float x);
	float linearInterpolation(float n0, float n1, float weight);
	float fadeFunction(float preFade);
}; 