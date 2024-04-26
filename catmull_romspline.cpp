#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;
#define int long long
#define width 100
#define height 100

// 1 1 1 1 1
// 1 A 1 1 1
// 1 1 1 1 1
// 1 1 1 1 1
// 1 1 1 1 1

struct Point
{
	float x;
	float y;
};

struct arrayIndex
{
	int row;
	int column;
};

arrayIndex CoordinateToIndex(Point coordinates)
{
	int x = (int)coordinates.x;
	int y = (int)coordinates.y;
	int column = x;
	int row = height - (y+1);
	arrayIndex temp;
	temp.row = row;
	temp.column = column;
	return (temp);
}
// 2d array[row][column]
Point IndexToCoordinate(pair<int, int> coordinates)
{
	int column = coordinates.second;
	int row = coordinates.first;
	int Coordinate_X = column;
	int Coordinate_Y = height - (row + 1);
	Point temp;
	temp.x = Coordinate_X;
	temp.y = Coordinate_Y;
	return (temp);
}
vector<Point> path;
Point CreateSpline(float t, bool bLooped = false){
	int p0, p1, p2, p3;
	if (!bLooped)
	{
		p1 = (int)t + 1;
		p2 = p1 + 1;
		p3 = p2 + 1;
		p0 = p1 - 1;
	}
	else
	{
		p1 = (int)t;
		p2 = (p1 + 1) % path.size();
		p3 = (p2 + 1) % path.size();
		p0 = p1 >= 1 ? p1 - 1 : path.size() - 1;
	}

	t = t - (int)t;

	float tt = t * t;
	float ttt = tt * t;

	float q1 = -ttt + 2.0f * tt - t;
	float q2 = 3.0f * ttt - 5.0f * tt + 2.0f;
	float q3 = -3.0f * ttt + 4.0f * tt + t;
	float q4 = ttt - tt;

	float tx = 0.5f * (path[p0].x * q1 + path[p1].x * q2 + path[p2].x * q3 + path[p3].x * q4);
	float ty = 0.5f * (path[p0].y * q1 + path[p1].y * q2 + path[p2].y * q3 + path[p3].y * q4);

	return {tx, ty};
}


signed main(){


	char map[height][width];
	memset(map, '.', sizeof(map));
	int NoOfpath = 7;
	//first n last dont matter
	path = {{100, 100}, {10, 41}, {30, 70}, {50, 41}, {70, 70}, {90, 41}, {100, 100}};

	//INPUT PATH
	/*
	cin>>NoOfpath;
	for(int x=0;x<NoOfpath;x++){
		Point temp;
		int row, column;
		cout<<"Enter row: ";
		cin>>row;
		cout<<'\n'<<"Ener column: ";
		cin>>column;
		temp = IndexToCoordinate(make_pair(row, column));
		path.push_back(temp);
	}

	for(int x=0;x<NoOfpath;x++){
		cout<<path[x].x<<" "<<path[x].y<<'\n';
	}
	*/
	
	int current_index = 1;

	path[0] = path[1];
	path[path.size()-1] = path[path.size()-2];
	memset(map, '.', sizeof(map));
	for (float t = 0; t < (float)NoOfpath - 3.0f; t += 0.1f){
		Point position = CreateSpline(t, false);
		arrayIndex hayden;
		hayden = CoordinateToIndex(position);
		map[hayden.row][hayden.column] = '0';
	}
	for(int x=1;x<path.size()-1;x++){
		arrayIndex temp = CoordinateToIndex(path[x]);
		map[temp.row][temp.column] = 'C';
	}

	arrayIndex temp = CoordinateToIndex(path[current_index]);
	map[temp.row][temp.column] = '?';
			
	//output

	for(int x=0;x<height;x++){
		for(int y=0;y<width;y++){
			cout<<map[x][y]<<" ";
		}
		cout<<'\n';
	}

	bool next = false, up = false, down = false, left = false, right = false, escape = false;
	while(true){
		bool changed = false;
		//input
		if (GetAsyncKeyState(VK_BACK) < 0 && next == false){
            next = true;
			if(current_index==1){
				current_index=path.size()-2;
			}
			else{
				current_index--;
			}
			changed = true;
        }
        if (GetAsyncKeyState(VK_BACK) == 0 && next == true)
        {
            next = false;
        }
		if (GetAsyncKeyState(VK_UP) < 0 && up == false){
			path[current_index].y += 5.0f;
            up = true;
			changed = true;
        }
        if (GetAsyncKeyState(VK_UP) == 0 && up == true)
        {
            up = false;
        }
		if (GetAsyncKeyState(VK_DOWN) < 0 && down == false){
			path[current_index].y -= 5.0f;
            down = true;
			changed = true;
        }
        if (GetAsyncKeyState(VK_DOWN) == 0 && down == true)
        {
            down = false;
        }
		if (GetAsyncKeyState(VK_LEFT) < 0 && left == false){
			path[current_index].x -= 5.0f;
            left = true;
			changed = true;
        }
        if (GetAsyncKeyState(VK_LEFT) == 0 && left == true)
        {
            left = false;
        }
		if (GetAsyncKeyState(VK_RIGHT) < 0 && right == false){
			path[current_index].x += 5.0f;
            right = true;
			changed = true;
        }
        if (GetAsyncKeyState(VK_RIGHT) == 0 && right == true)
        {
            right = false;
        }
        if (GetAsyncKeyState(VK_ESCAPE) < 0 && escape == false){
            escape = true;
            return 0;
        }
        if (GetAsyncKeyState(VK_ESCAPE) == 0 && escape == true)
        {
			escape = false;
        }

		if(changed){
			//changes
			cout << "\033[2J\033[1;1H";
			path[0] = path[1];
			path[path.size()-1] = path[path.size()-2];
			memset(map, '.', sizeof(map));
			for (float t = 0; t < (float)NoOfpath - 3.0f; t += 0.1f){
				Point position = CreateSpline(t, false);
				arrayIndex hayden;
				hayden = CoordinateToIndex(position);
				map[hayden.row][hayden.column] = '0';
			}
			for(int x=1;x<path.size()-1;x++){
				arrayIndex temp = CoordinateToIndex(path[x]);
				map[temp.row][temp.column] = 'C';
			}

			arrayIndex temp = CoordinateToIndex(path[current_index]);
			map[temp.row][temp.column] = '?';
			
			//output

			for(int x=0;x<height;x++){
				for(int y=0;y<width;y++){
					cout<<map[x][y]<<" ";
				}
				cout<<'\n';
			}
		}
	}
}