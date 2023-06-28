#include <math.h>
#include "Noise.h"

Noise::Noise(unsigned int num_tiles_y, unsigned int num_tiles_x)
{
	NUM_TILES_Y = num_tiles_y;
	NUM_TILES_X = num_tiles_x;
	int grid_dim_y = (int)ceil(NUM_TILES_Y / 5.0f);
	int grid_dim_x = (int)ceil(NUM_TILES_X / 5.0f);
	m_Grid = std::vector< std::vector<Vector2> >(grid_dim_y, std::vector<Vector2>(grid_dim_x, Vector2(0.0f, 0.0f))); // yucky syntax for 2D vector initialization!

	for (int y = 0; y < m_Grid.size(); y++)
	{
		for (int x = 0; x < m_Grid[y].size(); x++)
			// This step populates the grid with random, 2-dimensional unit-length gradient vectors that will be used in the Perlin Function
			m_Grid[y][x] = Vector2(true); 
	}

	m_Indexes = std::vector< std::vector<Vector2> >(NUM_TILES_Y, std::vector<Vector2>(NUM_TILES_X, Vector2(0.0f, 0.0f)));
	for (int y = 0; y < m_Indexes.size(); y++)
	{
		for (int x = 0; x < m_Indexes[y].size(); x++)
			m_Indexes[y][x] = Vector2(y / 20.0f, x / 20.0f);
	}

	m_NoiseArray = std::vector< std::vector<float> >(NUM_TILES_Y, std::vector<float>(NUM_TILES_X, 0.0f));
	for (int y = 0; y < m_NoiseArray.size(); y++)
	{
		for (int x = 0; x < m_NoiseArray[y].size(); x++)
			// This step generates noise based on the Perlin Function for a 2-Dimensional grid.
			m_NoiseArray[y][x] = PerlinFunction(m_Indexes[y][x].data[0], m_Indexes[y][x].data[1]);
	}
}


// For a 2-dimensional grid tile, the Perlin function consists of:
// 1) Defining 2^n random 2-dimensional unit-length gradient vectors at tile intersections. For a 2D tile, this would be 4 2-dimensional gradient vectors.
//     - this is done in the constructor loops above.
// 2) For each of the 4 "corners" of a tile, we compute an offset (displacement) vector from the corner to the particular x,y point of interest.
//		Then, we compute the dot products between the offset vectors and gradient vectors at each corner.
// 3) Finally, we interpolate between the 4 dot products from step 2.
float Noise::PerlinFunction(float y, float x)
{
	int y0 = (int)y;
	int x0 = (int)x;
	int y1 = y0 + 1;
	int x1 = x0 + 1;

	float wy = y - y0;
	float wx = x - x0;
	
	float dot1, dot2, dot3, dot4, lin1, lin2, preFade;
	dot1 = dotProduct(y0, x0, y, x);
	dot2 = dotProduct(y0, x1, y, x);
	lin1 = linearInterpolation(dot1, dot2, wx);
	dot3 = dotProduct(y1, x0, y, x);
	dot4 = dotProduct(y1, x1, y, x);
	lin2 = linearInterpolation(dot3, dot4, wx);
	preFade = linearInterpolation(lin1, lin2, wy);

	return fadeFunction(preFade);
}

void Noise::printNoise() const
{
	//TODO implement later for debugging?
}

float Noise::dotProduct(float gridy, float gridx, float y, float x)
{
	Vector2 A = computeOffsetVector(gridy, gridx, y, x);
	float aY = A.data[0];
	float aX = A.data[1];

	// A * B = aX*bX + aY*bY
	float result = aY * m_Grid[(int)gridy][(int)gridx].data[0] + aX * m_Grid[(int)gridy][(int)gridx].data[1];

	return result;
}

Vector2 Noise::computeOffsetVector(float gridy, float gridx, float y, float x)
{
	return Vector2(y - gridy, x - gridx);
}

float Noise::linearInterpolation(float n0, float n1, float weight)
{
	return n0 + weight * (n1 - n0);
}

float Noise::fadeFunction(float preFade)
{
	return (float)(6 * pow(preFade, 5.0f) - 15 * pow(preFade, 4.0f) + 10 * pow(preFade, 3.0f));
}

