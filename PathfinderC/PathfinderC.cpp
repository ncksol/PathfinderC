// PathfinderC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <complex>
using namespace std;

struct Node 
{
	int x, y;
};

struct Map
{
	int width, height;
	const unsigned char* pMap;

	Map(int width_, int height_, const unsigned char* pMap_) : width(width_), height(height_), pMap(pMap_)
	{
	}

	bool IsInBounds(Node id) const 
	{
		return 0 <= id.x && id.x < width && 0 <= id.y && id.y < height;
	}

	bool IsPassable(Node node) const
	{
		auto foo = pMap[node.x + node.y];
		return foo;
	}
  
	vector<Node> GetNeighbours(const Node id) const 
	{
		vector<Node> results;

		const Node nn{ id.x, id.y - 1 };
		const Node en{ id.x + 1, id.y };
		const Node sn{ id.x, id.y + 1 };
		const Node wn{ id.x - 1, id.y };

		if (IsPassable(nn) && IsInBounds(nn))
			results.push_back(nn);
		if (IsPassable(en) && IsInBounds(en))
			results.push_back(en);
		if (IsPassable(sn) && IsInBounds(sn))
			results.push_back(sn);
		if (IsPassable(wn) && IsInBounds(wn))
			results.push_back(wn);

		return results;
	}
};

double EstimateDistance(Node end, Node current)
{
	return abs(end.x - current.x) + abs(end.y - current.y);
}


int FindPath(const int nStartX, const int nStartY,
	const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
	int* pOutBuffer, const int nOutBufferSize)
{
	priority_queue<pair<Node, double>, vector<pair<Node, double>>, greater<pair<Node, double>>> frontier;
	map<Node, double> costsSoFar;
	map<Node, Node> cameFrom;
	Map map (nMapWidth, nMapHeight, pMap);

	Node start{ nStartX, nStartY};
	Node end{ nTargetX, nTargetY};

	frontier.push(pair<Node, double>(start, 0));
	cameFrom[start] = start;
	costsSoFar[start] = 0;

	bool targetFound;

	while (frontier.empty() == false)
	{
		pair<Node, double> current = frontier.top();
		frontier.pop();

		if(nTargetX == current.first.x && nTargetY == current.first.y)
		{
			targetFound = true;
			break;
		}
		
		for (Node neighbour : map.GetNeighbours(current.first))
		{
			double newCost = costsSoFar[current.first] + 1;
			if(costsSoFar.find(neighbour) == costsSoFar.end() || costsSoFar[neighbour] > newCost)
			{
				costsSoFar[neighbour] = newCost;
				cameFrom[neighbour] = current.first;
				double priority = newCost + EstimateDistance(end, neighbour);
				frontier.push(pair<Node, double>(neighbour, priority));
			}
		}
	}

	if(targetFound == false)
	{
		std::cout << "No path found";
		return  -1;
	}

	vector<Node> path;
	Node pathNode = end;
	while (pathNode.x != start.x && pathNode.y != start.y)
	{
		path.push_back(pathNode);
		pathNode = cameFrom[pathNode];
	}



}

int main()
{
	unsigned char pMap[] = { 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1 };
	int pOutBuffer[12];
	FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
