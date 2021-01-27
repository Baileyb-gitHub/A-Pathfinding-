#pragma once
using namespace std;


class Adjacency
{

	 int fromNodeX;
	 int fromNodeY;
	 int toNodeX;
	 int toNodeY;

	 // NOT SURE ABOUT BELOW YET, PICK NEEDED VARIABLES
public:
	void setup(int fromNodeXInput, int fromNodeYInput, int toNodeXInput, int toNodeYInput);
	int getToNodeX();
	int getToNodeY();
};

