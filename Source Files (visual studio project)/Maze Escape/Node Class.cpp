#include "Node.h"
#include "Adjacency.h"



void Node::setup(bool walkableInput, int xCordInput, int yCordInput, char mazeCharInput)
{
	walkableStatus = walkableInput;
	xCord = xCordInput;
	yCord = yCordInput;
	mazeChar = mazeCharInput;

}


void Node::addAdjacaency(Node adjacentNode)
{	
	Adjacency tempAdjacency;   // creates new adjacency
	tempAdjacency.setup(xCord, yCord, adjacentNode.xCord, adjacentNode.yCord);

	adjacencyList.push_back(tempAdjacency);
}




int Node::getXCord()
{
	return xCord;
}

int Node::getYCord()
{
	return yCord;
}

bool Node::getWalkableStatus()
{
	return walkableStatus;
}


int Node::getGCost()
{
	return gCost;
}

int Node::getHCost()
{
	return hCost;
}

int Node::getFCost()
{
	return gCost + hCost; // f cost calculated by combined g and h
}

Node * Node::getParent()
{
	return parent;
}
char Node::getMazeChar()
{
	return mazeChar;
}


void Node::setGCost(int newGCost)
{
	gCost = newGCost;
	
}

void Node::setHCost(int newHCost)
{
	hCost = newHCost;
}



void Node::setParent(Node newParent)
{
	parent = &newParent;
}
void Node::setParents(int newParentX, int newParentY)
{
	parentXCord = newParentX;
	parentYCord = newParentY;
}

int Node::getParentsX()
{
	return parentXCord;
}
int Node::getParentsY()
{
	return parentYCord;
}