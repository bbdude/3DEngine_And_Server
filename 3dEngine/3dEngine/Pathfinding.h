#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>

using namespace std;

class Astar
{
public:
	
	int n = 30; // horizontal size of the map
	int m = 30; // vertical size size of the map
	int map[30][30];
	int closed_nodes_map[30][30]; // map of closed nodes
	int open_nodes_map[30][30]; // map of open nodes
	int dir_map[30][30];
	const static int dir = 4;
	// if dir==4
	int dx[4];// = { 1, 0, -1, 0 };
	int dy[4];// = { 0, 1, 0, -1 };
	// if dir==8
	//static int dx[dir] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	//static int dy[dir] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	Astar();
	~Astar();
	string generate(int sx, int sy, int tx, int ty);
	class node
	{
		// current position
		int xPos;
		int yPos;
		// total distance already travelled to reach the node
		int level;
		// priority=level+remaining distance estimate
		int priority;  // smaller: higher priority

	public:
		node(int xp, int yp, int d, int p);

		int getxPos() const;
		int getyPos() const;
		int getLevel() const;
		int getPriority() const;

		void updatePriority(const int & xDest, const int & yDest);

		// give better priority to going strait instead of diagonally
		void nextLevel(const int & i);

		// Estimation function for the remaining distance to the goal.
		const int & estimate(const int & xDest, const int & yDest) const;
	};
	friend bool operator<(const node & a, const node & b);
	string pathFind(const int & xStart, const int & yStart,	const int & xFinish, const int & yFinish);

private:

};