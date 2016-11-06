#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

#define WIDTH 8
#define HEIGHT 8

void populate(bool grid[][WIDTH]) {
	int x;
	for (int y = 0; y < HEIGHT; ++y) {
		for (x = 0; x < WIDTH; x++) {
			grid[y][x] = false;
		}
	}
}
bool in_range(bool grid[][WIDTH],int x,int y) {
	return y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH && !grid[y][x];
}
void try_draw_option(bool grid[][WIDTH],int x,int y,string id,bool& firstOption) {
	if (in_range(grid,x,y)) {
		if (firstOption) {
			firstOption = false;
		} else {
			cout << ", ";
		}
		cout << id;
	}
}
void draw_options(bool grid[][WIDTH],int x,int y) {
	bool firstOption = true;
	cout << "Available movement directions: [";
	try_draw_option(grid,x,y - 1,"n",firstOption);
	try_draw_option(grid,x,y + 1,"s",firstOption);
	try_draw_option(grid,x - 1,y,"w",firstOption);
	try_draw_option(grid,x + 1,y,"e",firstOption);
	cout << "]" << endl;
}

int main() {
	bool grid[HEIGHT][WIDTH];
	populate(grid);

	grid[0][0] = true;
	grid[0][1] = true;
	grid[0][2] = true;
	grid[0][3] = true;
	grid[0][4] = true;
	grid[0][5] = true;
	grid[0][6] = true;
	grid[0][7] = true;
	grid[1][0] = true;
	grid[1][4] = true;
	grid[1][7] = true;
	grid[2][0] = true;
	grid[2][4] = true;
	grid[2][7] = true;
	grid[3][0] = true;
	grid[3][1] = true;
	grid[3][2] = true;
	grid[3][4] = true;
	grid[3][7] = true;
	grid[4][0] = true;
	grid[4][4] = true;
	grid[4][7] = true;
	grid[5][0] = true;
	grid[5][2] = true;
	grid[5][3] = true;
	grid[5][4] = true;
	grid[5][5] = true;
	grid[5][7] = true;
	grid[6][0] = true;
	grid[6][7] = true;
	grid[7][0] = true;
	grid[7][1] = true;
	grid[7][3] = true;
	grid[7][4] = true;
	grid[7][5] = true;
	grid[7][6] = true;
	grid[7][7] = true;

	int x = 2;
	int y = 7;
	string input;
	bool keepAlive;
	bool canMove;
	int newX;
	int newY;
	do {
		cout << "Current location: " << x << ", " << y << endl;
		draw_options(grid,x,y);
		cout << "Type q to quit." << endl;
		cin >> input;
		cout << endl;
		transform(input.begin(),input.end(),input.begin(),::tolower);
		keepAlive = input != "q";
		if (keepAlive) {
			newX = x;
			newY = y;
			canMove = true;
			if (input == "n") {
				newY--;
			} else if (input == "s") {
				newY++;
			} else if (input == "w") {
				newX--;
			} else if (input == "e") {
				newX++;
			} else {
				cout << "That is not a valid command." << endl;
				canMove = false;
			}
			if (canMove) {
				canMove = in_range(grid,newX,newY);
				if (canMove) {
					x = newX;
					y = newY;
				} else {
					cout << "Cannot move to that tile." << endl;
				}
			}
		}
	} while (keepAlive);
	return 0;
}