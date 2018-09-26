// PathfinderC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

struct Node {
	int x, y;
	bool isPassable;
};

struct SimpleGraph {
	map<char, vector<char> > edges;

	vector<char> neighbours(char id) {
		return edges[id];
	}
};

struct PriorityQueue {
	typedef pair<double, Node> PQElement;
	priority_queue<PQElement, vector<PQElement>, greater<PQElement>> elements;

	bool empty() const {
		return elements.empty();
	}

	void put(Node item, double priority) {
		elements.emplace(priority, item);
	}

	Node get() {
		Node best_item = elements.top().second;
		elements.pop();
		return best_item;
	}
};


struct SquareGrid{
	int width, height;

	SquareGrid(int width_, int height_) 
		: width(width_), height(height_) {}

	bool in_bounds(Node id) const {
		return 0 <= id.x && id.x < width
			&& 0 <= id.y && id.y < height;
	}
  
	vector<Node> neighbours(const Node id) const {
		vector<Node> results;

		const Node nn{ id.x, id.y - 1 };
		const Node en{ id.x + 1, id.y };
		const Node sn{ id.x, id.y + 1 };
		const Node wn{ id.x - 1, id.y };

		if (nn.isPassable && in_bounds(nn))
			results.push_back(nn);
		if (en.isPassable && in_bounds(en))
			results.push_back(en);
		if (sn.isPassable && in_bounds(sn))
			results.push_back(sn);
		if (wn.isPassable && in_bounds(wn))
			results.push_back(wn);

		return results;
	}
};


int FindPath(const int nStartX, const int nStartY,
	const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
	int* pOutBuffer, const int nOutBufferSize)
{
	priority_queue<tuple<int, int, int>,
	               vector<tuple<int, int, int>>,
	               greater<tuple<int, int, int>>> pq;
}

int main()
{
    cout << "Hello World!\n";

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
