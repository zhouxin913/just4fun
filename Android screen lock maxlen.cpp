#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>
#include <climits>

using namespace std;

struct Point {
  int x;
	int y;
	Point(int xx, int yy): x(xx), y(yy) {}
	void set(int xx, int yy) {
		x = xx;
		y = yy;
	}
};

bool v[3][3];
float maxlen;
vector<Point> path(9, Point(0, 0));
vector<Point> maxpath(9, Point(0, 0));

bool valid(int deep, Point start, Point end) {
	if (start.x == end.x && abs(start.y - end.y) == 2) {
		return v[start.x][(start.y + end.y)/2];
	}
	if (start.y == end.y && abs(start.x - start.x) == 2) {
		return v[(start.x + end.x)/2][start.y];
	}
	if (abs(start.x - start.y) == 2 && abs(start.y - end.y) == 2) {
		return v[1][1];
	}
	return true;
}

void dfs(int deep, Point start) {
	v[start.x][start.y] = true;
	path[deep] = start;

	if (deep == 8) {
		float sum = 0;
		for (int i = 1; i < 9; i++) sum += sqrt(float((path[i].x-path[i-1].x) * (path[i].x-path[i-1].x) + (path[i].y-path[i-1].y) * (path[i].y-path[i-1].y)));
		if (sum > maxlen) {
			maxlen = sum;
			maxpath = path;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (v[i][j]) continue;
			if (i == start.x && j == start.y) continue;
			if (!valid(deep, start, Point(i, j))) continue;
			dfs(deep+1, Point(i, j));
		}
	}
	v[start.x][start.y] = false;
}


int main() {
	memset(v, false, sizeof(v));
	maxlen = 0;
	
	Point p(0, 0);
	dfs(0, p);

	p.set(0, 1);
	dfs(0, p);

	p.set(1, 1);
	dfs(0, p);
	cout << maxlen << endl;
	for (int i = 0; i < 9; i++) {
		cout << maxpath[i].x << "---" << maxpath[i].y << endl;
	}

	system("PAUSE");
}
