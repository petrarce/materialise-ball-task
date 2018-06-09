#include <iostream>
#include <cmath>
#include "types.h"
#include "ball.h"

using namespace std;

Ball::Ball(Coord_t startPos, Coord_t startDir)
{

	curPos = startPos;
	speed  = sqrt(pow(startDir.x,2) + pow(startDir.y,2));
	curDir.x = startDir.x / speed;
	curDir.y = startDir.y / speed;
}

void Ball::GetPosition(Coord_t & box, double length)
{

	while(!CheckLength()){

		Shot(box);
		ChangeDir(box);
	}

	FixEndpoint();
}

bool Ball::CheckLength()
{

	if (currLength < targLength)
		return 0;
	
	return 1;
}

void Ball::Shot(Coord_t & box)
{
	//for all walls do:
		//find all points off crossig 
		//find all length from current to crossng point
	
	//sort all points by length from lowst to highest

	//for each point do:
		//if vector from curr point to crossing is colinear to direction
			//set current poing to rossing
		//else continue
}

void Ball::ChangeDir(Coord_t & box)
{
	if (curPos.x == box.x || curPos.x == 0)
		curDir.y *= -1;
	else
		curDir.x *= -1;
}

void Ball::FixEndpoint()
{

	double deltaLength = currLength - targLength;
	curPos.x -= curDir.x*deltaLength;
	curPos.y -= curDir.y*deltaLength;
}

Coord_t Ball::CrossPoint(Coord_t & p1, Coord_t & p2, Coord_t & vp1, Coord_t & vp2)
{

	Coord_t res;

	res.y = -1*
			(
				vp2.y*(p1.x * vp1.y - p1.y*vp1.x)-
				vp1.y*(p2.x * vp2.y - p2.y*vp2.x)
			) /
			(
				vp1.x*vp2.y -
				vp2.x*vp1.y
			);
	res.x = -1*
			(
				vp2.x*(p1.x * vp1.y - p1.y*vp1.x)-
				vp1.x*(p2.x * vp2.y - p2.y*vp2.x)
			) /
			(
				vp1.x*vp2.y -
				vp2.x*vp1.y
			);

	return res;
}