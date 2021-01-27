#include "Adjacency.h"
 


void Adjacency::setup(int fromNodeXInput, int fromNodeYInput, int toNodeXInput, int toNodeYInput)
{
	fromNodeX = fromNodeXInput;
	fromNodeY = fromNodeYInput;

	toNodeX = toNodeXInput;
	toNodeY = toNodeYInput;
}

int Adjacency::getToNodeX()
{
	return toNodeX;
}
int Adjacency::getToNodeY()
{
	return toNodeY;
}

