#include <math.h>
#include "Noise.h"

Noise::Noise(unsigned int num_tiles_y, unsigned int num_tiles_x)
{
	NUM_TILES_Y = num_tiles_y;
	NUM_TILES_X = num_tiles_x;
	int grid_dim_y = (int)ceil(NUM_TILES_Y / 5.0f);
	int grid_dim_x = (int)ceil(NUM_TILES_X / 5.0f);
	m_Grid = std::vector< std::vector<Vector2> >(grid_dim_y, std::vector<Vector2>(grid_dim_x, Vector2(0.0f, 0.0f))); // yucky syntax for 2D vector initialization!

	for (uint32_t y = 0; y < m_Grid.size(); y++)
	{
		for (uint32_t x = 0; x < m_Grid[0].size(); x++)
		{
			// This step populates the grid with random, 2-dimensional unit-length gradient vectors that will be used in the Perlin Function
			Vector2 v(true);
			//printf("Iteration: %i, v0: %.1f, v1: %.1f\n", x, v.v0(), v.v1());
			m_Grid[y][x] = v;
		}	
	}

	m_Indexes = std::vector< std::vector<Vector2> >(NUM_TILES_Y, std::vector<Vector2>(NUM_TILES_X, Vector2(0.0f, 0.0f)));
	for (uint32_t y = 0; y < NUM_TILES_Y; y++)
	{
		for (uint32_t x = 0; x < NUM_TILES_X; x++)
		{
			int iX = (int)x;
			int iY = (int)y;
			float facX = (float)(iX / 20);
			float facY = (float)(iY / 20);
			m_Indexes[y][x] = Vector2(facY, facX);
		}
			
	}

	m_NoiseArray = std::vector< std::vector<float> >(NUM_TILES_Y, std::vector<float>(NUM_TILES_X, 0.0f));
	for (uint32_t y = 0; y < NUM_TILES_Y; y++)
	{
		for (uint32_t x = 0; x < NUM_TILES_X; x++)
		{
			// This step generates noise based on the Perlin Function for a 2-Dimensional grid.
			float val = PerlinFunction(m_Indexes[y][x].v0(), m_Indexes[y][x].v1());
			m_NoiseArray[y][x] = val;
		}
	}
	printf("done\n");
}


// For a 2-dimensional grid tile, the Perlin function consists of:
// 1) Defining 2^n random 2-dimensional unit-length gradient vectors at tile intersections. For a 2D tile, this would be 4 2-dimensional gradient vectors.
//     - this is done in the constructor loops above.
// 2) For each of the 4 "corners" of a tile, we compute an offset (displacement) vector from the corner to the particular x,y point of interest.
//		Then, we compute the dot products between the offset vectors and gradient vectors at each corner.
// 3) Finally, we interpolate between the 4 dot products from step 2.
float Noise::PerlinFunction(float x, float y)
{
	float x0 = x;
	float x1 = x0 + 1.0f;
	float y0 = y;
	float y1 = y0 + 1.0f;

	float wx = x - x0;
	float wy = y - y0;
	
	float dot1, dot2, dot3, dot4, lin1, lin2, preFade;
	dot1 = dotProduct(x0, y0, x, y);
	dot2 = dotProduct(x1, y0, x, y);
	lin1 = linearInterpolation(dot1, dot2, wx);
	dot3 = dotProduct(x0, y1, x, y);
	dot4 = dotProduct(x1, y1, x, y);
	lin2 = linearInterpolation(dot3, dot4, wx);
	preFade = linearInterpolation(lin1, lin2, wy);

	return fadeFunction(preFade);
}

void Noise::printNoise() const
{
	//TODO implement later for debugging?
}

float Noise::dotProduct(float gridx, float gridy, float x, float y)
{
	Vector2 A = computeOffsetVector(gridx, gridy, x, y);
	float aY = A.v0();
	float aX = A.v1();

	Vector2 B = m_Grid[(int)gridy][(int)gridx];
	float bX = B.v1();
	float bY = B.v0();

	// A dot B = aX*bX + aY*bY
	float result = (float)((aX * bX) + (aY * bY));

	return result;
}

Vector2 Noise::computeOffsetVector(float gridx, float gridy, float x, float y)
{
	float newY = y - gridy;
	float newX = x - gridx;
	return Vector2(newY, newX);
}

float Noise::linearInterpolation(float n0, float n1, float weight)
{
	float result = n0 + (weight * (n1 - n0));
	return result;
}

float Noise::fadeFunction(float preFade)
{
	float result = 0.0f;
	float a = 6.0f * pow(preFade, 5.0f);
	float b = 15.0f * pow(preFade, 4.0f);
	float c = 10.0f * pow(preFade, 3.0f);

	result = a - b + c;
	return result;
	//return (float)(6 * pow(preFade, 5.0f) - 15 * pow(preFade, 4.0f) + 10 * pow(preFade, 3.0f));
}

