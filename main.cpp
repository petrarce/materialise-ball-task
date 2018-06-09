#include <iostream>
#include "ball.h"

using namespace std;



int main(int argc, char** argv)
{

	Ball ball;
	Coord_t a{1,1};
	Coord_t b{0,1};
	Coord_t av{-1,0};
	Coord_t bv{0,1};

	Coord_t c = ball.CrossPoint(a,b,av,bv);

	c = ball.CrossPoint(a,b,av,bv);

	cout << c.x << " " << c.y;
	return 0;
}

