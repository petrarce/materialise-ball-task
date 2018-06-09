#ifndef BALL_H
#define BALL_H

#include "types.h"

class Ball{
public:
	Coord_t curPos;
	Coord_t curDir;
	double speed;

	double currLength;
//private:
public: //uncomment previous and delete this. Just for debugging purpose
	void Shot(Coord_t & box);
	void ChangeDir(Coord_t & box);
	bool CheckLength(double targLength);
	void FixEndpoint(double targLength);
	Coord_t CrossPoint(Coord_t & p1, Coord_t & p2, Coord_t & vp1, Coord_t & vp2);

public:
	Ball(){};
	Ball(Coord_t startPos, Coord_t startDir);
	void SetDirection(Coord_t);
	void SetSpeed(double);
	void SetPosition(Coord_t);
	Coord_t GetPosition(Coord_t & box, double length);
};

#endif //BALL_H