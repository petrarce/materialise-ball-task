#include <iostream>
#include <cmath>
#include "types.h"
#include "ball.h"

using namespace std;

struct CurPointLength{
	Coord_t pt;
	Coord_t dir;
	double length;
};
typedef struct CurPointLength CurPointLength_t;

#define EPS 0.0001

Coord_t decartStart{0,0};
Coord_t oxVect{0,1};
Coord_t oyVect{1,0};


Ball::Ball(Coord_t startPos, Coord_t startDir)
{

	curPos = startPos;
	speed  = sqrt(pow(startDir.x,2) + pow(startDir.y,2));
	curDir.x = startDir.x / speed;
	curDir.y = startDir.y / speed;
}

Coord_t Ball::GetPosition(Coord_t & box, double length)
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
	CurPointLength_t points[4];
	
	//find all  crossig points
	points[0].pt = CrossPoint(decartStart,	curPos, oxVect, curDir);
	points[1].pt = CrossPoint(decartStart,	curPos, oyVect, curDir);
	points[2].pt = CrossPoint(box,			curPos, oxVect, curDir);
	points[3].pt = CrossPoint(box,			curPos, oyVect, curDir);

	//find all length from current to crossng point
	for(int i = 0; i < 4; i++){
		points[i].length = sqrt(
								pow(curPos.x - points[i].pt.x,2) +
								pow(curPos.y - points[i].pt.y,2)
							);
		points[i].dir.x = points[i].pt.x - curPos.x;
		points[i].dir.y = points[i].pt.y - curPos.y;
	}

	
	//sort all points by length from lowst to highest.
	//use boble for sorting
	for (int i = 0; i < 4; i++){
		for (int j = i+1; j < 4; j++){
			if (points[i].length > points[j].length){
				CurPointLength_t temp;
				temp = points[i];
				points[i] = points[j];
				points[j] = temp;
			}
		}
	}

	//Determine which vectors are semidirectional
	for (int i = 0; i < 4; i++){

		if(points[i].dir.x*curDir.x < 0 ||  points[i].dir.y*curDir.y < 0)
			continue;

		curPos = points[i].pt;
		currLength += points[i].length;
		return;
	}

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

	//TODO: check if lines are colinear
	//TODO: check if points (with respect to direction vectors) are belong to one line
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