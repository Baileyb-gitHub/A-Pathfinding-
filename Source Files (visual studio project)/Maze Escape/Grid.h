#pragma once
#include "Node.h"
#include "errorHandler.h"
#include <vector>
#include <list>
using namespace std;

class Grid  //stores a gride of nodes representing maze characters and performs a* search algorith on the grid
{
	bool routeCalculated = false;
	string routeSolution;

	Node startNode;
	Node exitNode;

	int loopCap = 500;  //maximum number of loops allowed in the  search before no path error declared

	vector<vector<Node>> nodeGrid;  //2d vector used to represent maze file

	vector<Node> openList; //list of nodes to be evaluated for a* calculation
	vector<Node> closedList; // list of evaluated nodes for a* calculation

public:
	void addToGrid(vector<Node> nodesToAdd);
	void setStartNode(Node startNodeInput);
	void setExitNode(Node exitNodeInput);
	void calculateNodeAdjacencies();
	string retracePath(Node startNode, Node endNode);
	string calculateMazeSolution();
	void printGrid();

	



};

