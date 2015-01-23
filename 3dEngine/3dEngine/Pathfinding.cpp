#include "stdafx.h"
#include "Pathfinding.h"

Astar::Astar()
{
	int tempDx[4] = { 1, 0, -1, 0 };
	int tempDy[4] = { 0, 1, 0, -1 };
	memcpy(dx, tempDx, sizeof(dx));
	memcpy(dy, tempDy, sizeof(dy));
}
Astar::~Astar()
{}
string Astar::generate(int sx, int sy, int tx, int ty)
{

	// empty map generator
	for (int y = 0; y < m; y++)
	{
		for (int x = 0; x < n; x++) map[x][y] = 0;
	}

	//wall setting (cross form in the middle)
	for (int i = 5; i < 25; i++)
	{
		map[i][m / 2] = 1;
	}for (int i = 5; i < 25; i++)
	{
		map[n / 2][i] = 1;
	}
	if (map[tx][ty] != 1)
	{
		string route = pathFind(sx, sy, tx, ty);
		//if (route == "") cout << "An empty route generated!" << " " << sx << " " << sy << " " << tx << " " << ty << endl;
		return route;
	}
	if (sx == tx && sy == ty)
	{
		//cout << "Goal reached!" << endl;
	}
	else
	{
		//cout << "Cannot go into a wall" << endl;;
		return "";
	}
}
bool operator< (const Astar::node & a, const  Astar::node & b)
{
	return a.getPriority() > b.getPriority();
}
string Astar::pathFind(const int & xStart, const int & yStart, const int & xFinish, const int & yFinish)
{
	static priority_queue<node> pq[2]; // list of open nodes
	static int pqi; // priority_queue index
	static node* n0; //node
	static node* m0; //node
	static int i, j, x, y, xdx, ydy;
	static char c;
	pqi = 0;

	// reset the node maps
	for (y = 0; y<m; y++)
	{
		for (x = 0; x<n; x++)
		{
			closed_nodes_map[x][y] = 0;
			open_nodes_map[x][y] = 0;
		}
	}

	// create the start node and push into list of open nodes
	n0 = new node(xStart, yStart, 0, 0);
	n0->updatePriority(xFinish, yFinish);
	pq[pqi].push(*n0);
	open_nodes_map[xStart][yStart] = n0->getPriority();  // mark it on the open nodes map

	// A* search
	while (!pq[pqi].empty())
	{
		// get the current node w/ the highest priority
		// from the list of open nodes
		//delete n0;
		n0 = new node(pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
			pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

		x = n0->getxPos(); y = n0->getyPos();

		pq[pqi].pop(); // remove the node from the open list
		open_nodes_map[x][y] = 0;
		// mark it on the closed nodes map
		closed_nodes_map[x][y] = 1;

		// quit searching when the goal state is reached
		//if((*n0).estimate(xFinish, yFinish) == 0)
		if (x == xFinish && y == yFinish)
		{
			// generate the path from finish to start
			// by following the directions
			string path = "";
			while (!(x == xStart && y == yStart))
			{
				j = dir_map[x][y];
				c = '0' + (j + dir / 2) % dir;
				path = c + path;
				x += dx[j];
				y += dy[j];
			}
			delete n0;
			while (!pq[pqi].empty()) pq[pqi].pop();
			return path;
		}

		// generate moves in all possible directions
		for (i = 0; i<dir; i++)
		{
			xdx = x + dx[i]; ydy = y + dy[i];

			if (!(xdx<0 || xdx>n - 1 || ydy<0 || ydy>m - 1 || map[xdx][ydy] == 1
				|| closed_nodes_map[xdx][ydy] == 1))
			{
				// generate a child node

				m0 = new node(xdx, ydy, n0->getLevel(),
					n0->getPriority());
				m0->nextLevel(i);
				m0->updatePriority(xFinish, yFinish);

				// if it is not in the open list then add into that
				if (open_nodes_map[xdx][ydy] == 0)
				{
					open_nodes_map[xdx][ydy] = m0->getPriority();
					pq[pqi].push(*m0);
					// mark its parent node direction
					dir_map[xdx][ydy] = (i + dir / 2) % dir;
				}
				else if (open_nodes_map[xdx][ydy]>m0->getPriority())
				{
					open_nodes_map[xdx][ydy] = m0->getPriority();
					dir_map[xdx][ydy] = (i + dir / 2) % dir;

					// replace the node
					// by emptying one pq to the other one
					// except the node to be replaced will be ignored
					// and the new node will be pushed in instead
					while (!(pq[pqi].top().getxPos() == xdx &&
						pq[pqi].top().getyPos() == ydy))
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pq[pqi].pop(); // remove the wanted node
					//delete m0;

					if (pq[pqi].size()>pq[1 - pqi].size()) pqi = 1 - pqi;
					while (!pq[pqi].empty())
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(*m0); // add the better node instead
				}
				else delete m0;
			}
		}
		delete n0;
	}
	return ""; // no route found
}

Astar::node::node(int xp, int yp, int d, int p)
{
	xPos = xp; yPos = yp; level = d; priority = p;
}

int Astar::node::getxPos() const
{ 
	return xPos; 
}
int Astar::node::getyPos() const 
{ 
	return yPos; 
}
int Astar::node::getLevel() const
{ 
	return level; 
}
int Astar::node::getPriority() const
{ 
	return priority; 
}

void Astar::node::updatePriority(const int & xDest, const int & yDest)
{
	priority = level + estimate(xDest, yDest) * 10; //A*
}

void Astar::node::nextLevel(const int & i) // i: direction
{
	level += (dir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
}

const int & Astar::node::estimate(const int & xDest, const int & yDest) const
{
	static int xd, yd, d;
	xd = xDest - xPos;
	yd = yDest - yPos;

	// Euclidian Distance
	d = static_cast<int>(sqrt(xd*xd + yd*yd));

	// Manhattan distance
	//d=abs(xd)+abs(yd);

	// Chebyshev distance
	//d=max(abs(xd), abs(yd));

	return(d);
}