#ifndef TYPES_H
#define TYPES_H
#include <cmath>

using namespace std;

struct Coord{
	double x;
	double y;
};
typedef struct Coord Coord_t;

static double custom_round(double val, int exp)
{
	double temp = round(val*exp); 
	return temp/exp;
}

#endif //TYPES_H