/*
 * PathPlanner.cpp
 */

#include "PathPlanner.h"
#include "ConfigurationManager.h"
#include "Map.h"
#include "lodepng.h"
#include <iostream>
#include <math.h>
#include <queue>


using namespace std;

class Node
{
	// current position
    int xPos;
    int yPos;

    // total distance already travelled to reach the node
    int level;

    // priority=level+remaining distance estimate
    int priority;  // smaller: higher priority

    public:
        Node(int xp, int yp, int d, int p)
            {xPos=xp; yPos=yp; level=d; priority=p;}

        int getxPos() const {return xPos;}
        int getyPos() const {return yPos;}
        int getLevel() const {return level;}
        int getPriority() const {return priority;}

        void updatePriority(const int & xDest, const int & yDest)
        {
             priority=level+estimate(xDest, yDest)*10; //A*
        }

        // give better priority to going strait instead of diagonally
        void nextLevel(const int & i) // i: direction
        {
             if (i % 2 == 0)
             {
            	 level += 10;

             }else
             {
            	 level += 14;
             }
        }

        // Estimation function for the remaining distance to the goal
        const int & estimate(const int & xDest, const int & yDest) const
        {
            static int xd, yd, dist;
            xd=xDest-xPos;
            yd=yDest-yPos;

            //Distance
            dist=static_cast<int>(sqrt(xd*xd+yd*yd));

            return(dist);
        }
};

// Determine priority
bool operator<(const Node & nodeA, const Node & nodeB)
{
  return nodeA.getPriority() > nodeB.getPriority();
}

void PathPlanner::PrintPath(int** GridMap,const int nRowStart, const int nColStart, const int Hight, const int Width, string route)
{
	// follow the route on the map and display it
		if (route.length() > 0)
		{
			int direction;
			char c;
			unsigned int x = nRowStart;
			unsigned int y = nColStart;
			GridMap[x][y] = 2;
			for (unsigned int i = 0; i < route.length(); i++)
			{
				c = route.at(i);
				direction = c-'0';
				x += dirX[direction];
				y += dirY[direction];
				GridMap[x][y] = 3;
			}
			GridMap[x][y] = 4;

			// display the map with the route
			for (int x = 0; x < Hight; x++)
			{
				for (int y = 0; y < Width; y++)
				{
					if (GridMap[x][y] == 0)
					cout << ".";
					else if (GridMap[x][y] == 1)
					cout << "O"; //obstacle
					else if (GridMap[x][y] == 2)
					cout << "S"; //start
					else if (GridMap[x][y] == 3)
					cout << "R"; //route
					else if (GridMap[x][y] == 4)
					cout << "F"; //finish
					else if (GridMap[x][y] == 5)
					cout << "P"; //particle

				}
				cout << endl;
			}
		}
		else
		{
			cout << "No route found";
			cout << endl;
		}
}

string PathPlanner::AStarPathFind( const int nRowStart, const int nColStart,
                 const int nRowFinish, const int nColFinish, int** GridMap, const int Hight, const int Width )
{
	int closed_nodes_map[Hight][Width]; // map of closed (tried-out) nodes
	int open_nodes_map[Hight][Width]; // map of open (not-yet-tried) nodes
	int dir_map[Hight][Width];
	static priority_queue<Node> prior_queue[2]; // list of open (not-yet-tried) nodes
    static int pqIndex; // Priority queue index
    static Node* nNodeA;
    static Node* nNodeB;
    static int dirIndex, cellIndex, RowIndex, ColIndex, xdx, ydy;
    static char c;
    pqIndex=0;


    // Initialize the cells in the maps
    for(RowIndex = 0;RowIndex < Hight;RowIndex++)
    {
		for(ColIndex = 0;ColIndex < Width;ColIndex++)
		{
            closed_nodes_map[RowIndex][ColIndex]=0;
            open_nodes_map[RowIndex][ColIndex]=0;
        }
    }

    // create the start node and push into list of open nodes
    nNodeA=new Node(nRowStart, nColStart, 0, 0);
    nNodeA->updatePriority(nRowFinish, nColFinish);
    prior_queue[pqIndex].push(*nNodeA);
    open_nodes_map[RowIndex][ColIndex]=nNodeA->getPriority(); // mark it on the open nodes map

    // A* search
    while(!prior_queue[pqIndex].empty())
    {
        // get the current node w/ the highest priority
        // from the list of open nodes
    	nNodeA=new Node( prior_queue[pqIndex].top().getxPos(), prior_queue[pqIndex].top().getyPos(),
    					prior_queue[pqIndex].top().getLevel(), prior_queue[pqIndex].top().getPriority());

        RowIndex=nNodeA->getxPos();
        ColIndex=nNodeA->getyPos();

        prior_queue[pqIndex].pop(); // remove the node from the open list
        open_nodes_map[RowIndex][ColIndex]=0;
        // mark it on the closed nodes map
        closed_nodes_map[RowIndex][ColIndex]=1;

        // quit searching when the goal state is reached
        //if((*nodeA).estimate(xFinish, yFinish) == 0)
        if(RowIndex==nRowFinish && ColIndex==nColFinish)
        {
            // generate the path from finish to start
            // by following the directions
            string path="";
            while(!(RowIndex==nRowStart && ColIndex==nColStart))
            {
            	cellIndex=dir_map[RowIndex][ColIndex];
                c='0'+(cellIndex+dirNum/2)%dirNum;
                path=c+path;
                RowIndex+=dirX[cellIndex];
                ColIndex+=dirY[cellIndex];
            }

            // delete node
            delete nNodeA;

            // delete all left nodes
            while(!prior_queue[pqIndex].empty()) prior_queue[pqIndex].pop();
            return path;
        }

        // generate moves possible moves
        for(dirIndex=0;dirIndex<dirNum;dirIndex++)
        {
            xdx=RowIndex+dirX[dirIndex];
            ydy=ColIndex+dirY[dirIndex];

            if(!(xdx<0 || xdx>Hight-1 || ydy<0 || ydy>Width-1 || GridMap[xdx][ydy]==1
                || closed_nodes_map[xdx][ydy]==1))
            {
                // generate a child node
            	nNodeB=new Node( xdx, ydy, nNodeA->getLevel(),
                		nNodeA->getPriority());
            	nNodeB->nextLevel(dirIndex);
            	nNodeB->updatePriority(nRowFinish, nColFinish);

                // if it is not in the open list then add into that
                if(open_nodes_map[xdx][ydy]==0)
                {
                    open_nodes_map[xdx][ydy]=nNodeB->getPriority();
                    prior_queue[pqIndex].push(*nNodeB);
                    // mark its parent node direction
                    dir_map[xdx][ydy]=(dirIndex+dirNum/2)%dirNum;
                }
                else if(open_nodes_map[xdx][ydy]>nNodeB->getPriority())
                {
                    // update the priority info
                    open_nodes_map[xdx][ydy]=nNodeB->getPriority();
                    // update the parent direction info
                    dir_map[xdx][ydy]=(dirIndex+dirNum/2)%dirNum;

                    /* replace the node by emptying one priority queue to the other one
                     except the node to be replaced will be ignored and the new node will be pushed in instead*/
                    while(!(prior_queue[pqIndex].top().getxPos()==xdx &&
                    		prior_queue[pqIndex].top().getyPos()==ydy))
                    {
                    	prior_queue[1-pqIndex].push(prior_queue[pqIndex].top());
                    	prior_queue[pqIndex].pop();
                    }

                    // remove the wanted node
                    prior_queue[pqIndex].pop();

                    // empty the larger size priority queue to the smaller one
                    if(prior_queue[pqIndex].size()>prior_queue[1-pqIndex].size()) pqIndex=1-pqIndex;
                    while(!prior_queue[pqIndex].empty())
                    {
                    	prior_queue[1-pqIndex].push(prior_queue[pqIndex].top());
                    	prior_queue[pqIndex].pop();
                    }
                    pqIndex=1-pqIndex;
                    prior_queue[pqIndex].push(*nNodeB); // add the better node instead
                }
                else delete nNodeB;
            }
        }
        delete nNodeA;
    }

    // no route found
    return "";
}
