#pragma once
#include "Adjacency.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node
{


	bool walkableStatus;

	int xCord;
	int yCord;
	
	int gCost; // cost representing distance from start node
	int hCost; // cost representing distance from exit node
	Node * parent;

	int parentXCord;
	int parentYCord;

	char mazeChar; // textfile character of node, used for debugging / providing info in the print grid function
	
	


public:
	void setup(bool walkableInput, int xCordInput, int yCordInput, char mazeCharInput);
	void addAdjacaency(Node adjacentNode);
	


	int getXCord();
	int getYCord();
	bool getWalkableStatus();
	int getGCost();
	int getHCost();
	int getFCost();
	Node * getParent();
	int    getParentsX();
	int    getParentsY();
	char getMazeChar();

	void setGCost(int newGCost);
	void setHCost(int newGCost);
	
	void setParent(Node newParent);
	void setParents(int newParentX, int newParentY);
	vector<Adjacency> adjacencyList;

	

	bool operator == (Node node)
	{
		if (xCord == node.xCord && yCord == node.yCord)
		{
			return true;
		}
		return false;
	}

	bool operator != (Node node)
	{
		if (xCord != node.xCord || yCord != node.yCord)
		{
			return true;
		}
		return false;
	}
};

