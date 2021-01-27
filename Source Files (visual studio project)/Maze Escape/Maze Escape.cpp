// Maze Escape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include <iostream>
#include <string>
#include <fstream>

#include "Grid.h" 
#include "errorHandler.h"

using namespace std; // 






int main()
{
    string inputFileName;// name of input file, used to write solution to corresponding named file
    string mazeSolution; // string to hold maze solutiom
    Grid mazeGrid; // grid used to store map nodes and execute pathfinding
   
  
    cout << "Please enter the maze file name (eg maze1) - ";
    getline(std::cin, inputFileName);

    ifstream mazeFile;
    mazeFile.open(inputFileName + ".txt");

    if (mazeFile.fail())
    {
        returnError("Could not find your file, was the name entered correctly ? (Caps sensitive)");
    }
    else
    {
        string lineString;
      
        
        int xPos = 0;
        int yPos = 0;
        while (getline(mazeFile, lineString))
        {
            vector<Node> gridLine;  // create grid array for this line

            for (char const& c : lineString) {  // for each character in the text file line, create a node and add it to the vector representing this line in the node grid 
                Node newNode;

                if(c == 'x')
                {
                    newNode.setup(false, xPos, yPos, c);
                }
                else
                {
                    newNode.setup(true, xPos, yPos, c);

                    if(c == 'A')
                    {
                        mazeGrid.setStartNode(newNode);
                    }
                    else if (c == 'B')
                    {
                        mazeGrid.setExitNode(newNode);
                    }
          
                }
                gridLine.push_back(newNode);
                xPos += 1;   
            }

            yPos += 1;
            xPos = 0;
            cout << endl;
            mazeGrid.addToGrid(gridLine);     // add completed line to the node grid
        }
    }
  
    mazeFile.close();


    mazeGrid.calculateNodeAdjacencies();  
    mazeSolution = mazeGrid.calculateMazeSolution();

    cout << "\nHere is the maze solution - " << mazeSolution << endl;

    cout << "would you like the solution written to a file ? (yes/no) : ";

    string response;
    getline(std::cin,response);

    if(response == "yes")
    {
        ofstream solutionFile;
        solutionFile.open(inputFileName + " Solution.txt");

        solutionFile << "Solution to the maze is - " << mazeSolution;
        solutionFile.close();
    }


    return 0;
}



