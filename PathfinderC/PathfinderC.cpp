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

bool operator == (Node a, Node b)
{
	return a.x == b.x && a.y == b.y;
}

bool operator != (Node a, Node b)
{
	return !(a == b);
}

bool operator < (Node a, Node b)
{
	return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

struct Graph
{
	int width, height;
	const unsigned char* pMap;

	Graph(int width_, int height_, const unsigned char* pMap_) : width(width_), height(height_), pMap(pMap_)
	{
	}

	bool IsInBounds(Node node) const
	{
		return 0 <= node.x && node.x < width && 0 <= node.y && node.y < height;
	}

	bool IsPassable(Node node) const
	{
		return  pMap[node.x + node.y*width];
	}

	vector<Node> GetNeighbours(const Node node) const
	{
		vector<Node> results;

		const Node nn{ node.x, node.y - 1 };
		const Node en{ node.x + 1, node.y };
		const Node sn{ node.x, node.y + 1 };
		const Node wn{ node.x - 1, node.y };

		if (IsInBounds(nn) && IsPassable(nn))
			results.push_back(nn);
		if (IsInBounds(en) && IsPassable(en))
			results.push_back(en);
		if (IsInBounds(sn) && IsPassable(sn))
			results.push_back(sn);
		if (IsInBounds(wn) && IsPassable(wn))
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
	Graph graph(nMapWidth, nMapHeight, pMap);

	Node start{ nStartX, nStartY };
	Node end{ nTargetX, nTargetY };

	frontier.push(pair<Node, double>(start, 0));
	cameFrom[start] = start;
	costsSoFar[start] = 0;

	auto targetFound = false;

	while (frontier.empty() == false)
	{
		auto current = frontier.top().first;
		frontier.pop();

		if (nTargetX == current.x && nTargetY == current.y)
		{
			targetFound = true;
			break;
		}

		for (auto neighbour : graph.GetNeighbours(current))
		{
			auto newCost = costsSoFar[current] + 1;
			if (costsSoFar.find(neighbour) == costsSoFar.end() || costsSoFar[neighbour] > newCost)
			{
				costsSoFar[neighbour] = newCost;
				cameFrom[neighbour] = current;
				auto priority = newCost + EstimateDistance(end, neighbour);
				frontier.push(pair<Node, double>(neighbour, priority));
			}
		}
	}

	if (targetFound == false)
	{		
		return  -1;
	}

	vector<int> path;
	auto pathNode = end;
	while (pathNode != start)
	{
		path.push_back(pathNode.x + pathNode.y*nMapWidth);
		pathNode = cameFrom[pathNode];
	}

	reverse(path.begin(), path.end());

	if (path.size() > nOutBufferSize)
		return -1;

	pOutBuffer = &path[0];

	return path.size();
}

int main()
{
	unsigned char pMap[] = { 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1 };
	int pOutBuffer[12];
	auto length = FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);
	cout << length;
}
