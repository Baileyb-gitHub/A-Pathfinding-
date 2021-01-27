#include "Grid.h"
#include <math.h>
#include <iostream>

void Grid::addToGrid(vector<Node> nodesToAdd)
{
    nodeGrid.push_back(nodesToAdd);
}



void Grid::setStartNode(Node startNodeInput) // assigns the start node variable of grid and returns error if start node has already been set
{
   if(startNode.getMazeChar() == 'A') // signifies node already defined      
   {
       returnError("multiple start positions given, please check maze layout and ensure only one start position is given ");
   }
   else
   {
       startNode = startNodeInput;
   }
      
}
void Grid::setExitNode(Node exitNodeInput) // assigns the exit node variable of grid and returns error if start node has already been set
{
    if (exitNode.getMazeChar() == 'B') // signifies node already defined
    {
        returnError("multiple exit positions given, please check maze layout and ensure only one exit position is given ");
    }
    else
    {
        exitNode = exitNodeInput;
    }
}

void Grid::calculateNodeAdjacencies()  // for each node in grid checks if nodes exist above, below, left, right, and add them as adjacancies if so
{
    if(startNode.getWalkableStatus() == false) // if startnodes walkable is false it hasnt been assigned so an error should be returned before a failed path calculation is made
    {
        returnError("0 start positions given, please check maze layout and ensure one exit position is given ");
    }
    if (exitNode.getWalkableStatus() == false) // if exitnodes walkable is false it hasnt been assigned so an error should be returned before a failed path calculation is made
    {
        returnError("0 exit positions given, please check maze layout and ensure one exit position is given ");
    }

    for (int i = 0; i < nodeGrid.size(); i++)
    {
        for (int j = 0; j < nodeGrid[i].size(); j++)
        {

       
            if (i - 1 > -1)
            {
                nodeGrid[i][j].addAdjacaency(nodeGrid[i-1][j]);
            }
          
            if (i + 1 < nodeGrid.size())
            {
              nodeGrid[i][j].addAdjacaency(nodeGrid[i+1][j]);
            }

          
            if (j - 1 > -1)
            {
                nodeGrid[i][j].addAdjacaency(nodeGrid[i][j-1]);
            }

           
            if(j + 1 < nodeGrid[i].size())
            {
                nodeGrid[i][j].addAdjacaency(nodeGrid[i][j+1]);
            }
        }

    }

    startNode.adjacencyList = nodeGrid[startNode.getYCord()][startNode.getXCord()].adjacencyList; //updates start node adjacencies from grid
    exitNode.adjacencyList = nodeGrid[startNode.getYCord()][startNode.getXCord()].adjacencyList; //updates end node adjacencies from grid

}


int calculateDistance(Node node1, Node node2)  // gives distance between nodes  as int 
{
    int xDistance = abs(node1.getXCord() - node2.getXCord());
    int yDistance = abs(node1.getYCord() - node2.getYCord());

    if(xDistance > yDistance)
    {
        return 14 * yDistance + 10 * (xDistance - yDistance);
    }
    return 14 * xDistance + 10 * (yDistance - xDistance);
}

string Grid::retracePath(Node startNode, Node endNode)
{
    


    string path;

    Node currentNode = endNode;
    while(currentNode != startNode)  // goes backwards from end node to start by following node parents
    {
        if (currentNode.getParentsX() < currentNode.getXCord())
        {
            path = "E" + path;   // as the path is working back to front new directions are inserted at the front of the string to flip the path the right way round
        }
        else if (currentNode.getParentsX() > currentNode.getXCord())
        {
            path = "W" + path;
        }
        else if (currentNode.getParentsY() > currentNode.getYCord())
        {
            path = "N" + path;
        }
        else if (currentNode.getParentsY() < currentNode.getYCord())
        {
            path = "S" + path;
        }

        currentNode = nodeGrid[currentNode.getParentsY()][currentNode.getParentsX()]; 
    }
    return path;
}

string Grid::calculateMazeSolution()
{
    int loopCount = 0;
    Node currentNode; // currently assessed node for a* calculation
    Node Neighbour; // currently assessed neighbour node 


    openList.push_back(nodeGrid[startNode.getYCord()][startNode.getXCord()]);
    
    while (routeCalculated != true)
    {
        if(openList.size() == 0)
        {
            returnError("No path found, please check maze layout and ensure a path from A to B is possible");
        }

        currentNode = openList[0];
        int currentPos = 0;

        for (int i = 1; i < openList.size(); i++)   // checks all nodes in open list to find lowest f cost and sets this to current node, moving it from open to closed/explored
        {
           if(openList[i].getFCost() < currentNode.getFCost() || openList[i].getFCost() == currentNode.getFCost()  && openList[i].getHCost() < currentNode.getHCost())   // if node has lower distance to exit or same distance to exit with less distance from start then this becomes new current node
           {
               currentNode = openList[i];              
               currentPos = i;
           }
        }
        closedList.push_back(currentNode);
        openList.erase(openList.begin() + currentPos);
      

        if(currentNode.getMazeChar() == 'B')   // if current node is B then exit has been located
        {
            routeCalculated = true;
            cout << "PATH CALCULATED" << endl;
            return  ( retracePath( nodeGrid[startNode.getYCord()][startNode.getXCord()] , nodeGrid[exitNode.getYCord()][exitNode.getXCord()])   );
        }

        for (int i = 0; i < currentNode.adjacencyList.size(); i++)
        {
            Neighbour = nodeGrid[currentNode.adjacencyList[i].getToNodeY()][currentNode.adjacencyList[i].getToNodeX()];     

            if (Neighbour.getWalkableStatus() == false || find(closedList.begin(), closedList.end(), Neighbour) != closedList.end())   // ignore adjacent node if impassable or alredy in closed list         
            {

                continue;
            }
            
            int newMovementDistance = currentNode.getGCost() + calculateDistance(currentNode, Neighbour) ; 

            if(newMovementDistance < Neighbour.getGCost() || find(openList.begin(), openList.end(), Neighbour) == openList.end()   )
            {
               

        
            nodeGrid[Neighbour.getYCord()][Neighbour.getXCord()].setGCost(newMovementDistance);

            nodeGrid[Neighbour.getYCord()][Neighbour.getXCord()].setHCost(calculateDistance(Neighbour, exitNode));

           
            nodeGrid[Neighbour.getYCord()][Neighbour.getXCord()].setParents(currentNode.getXCord(), currentNode.getYCord());

            if(find(openList.begin(), openList.end(), Neighbour) == openList.end())
              {
                openList.push_back(Neighbour);
              }
            }         
        }
        loopCount += 1;
        if(loopCount > loopCap)
        {
            returnError("No path found, not possible to reach exit or loop cap is too small");
        }
    }
}


void Grid::printGrid()   // prints out details of the node grid, used for testing and debugging    **call printGrid() after calling calculateAdjacencies for full information**
{
  
    cout << "now printing node grid \n"; 

    for (int i = 0; i < nodeGrid.size(); i++)
    {
        for (int j = 0; j < nodeGrid[i].size(); j++)
        {
           
            cout << " Coords- " << nodeGrid[i][j].getXCord() << "," << nodeGrid[i][j].getYCord() << "    Character- " << nodeGrid[i][j].getMazeChar()<< "    Number of adjacencies- " << nodeGrid[i][j].adjacencyList.size() <<endl;

        }
        cout << endl;
    }

    cout << "now printing Start Node Info \n";
    cout << startNode.getXCord() << "," << startNode.getYCord() << "    Character- " << startNode.getMazeChar() << "    Number of adjacencies- " << startNode.adjacencyList.size() << endl;
 
    
    cout << "now printing Exit Node Info \n";
    cout << exitNode.getXCord() << "," << exitNode.getYCord() << "    Character- " << exitNode.getMazeChar() << "    Number of adjacencies- " << exitNode.adjacencyList.size() << endl;
}


