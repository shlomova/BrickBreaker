#pragma once

#include <stdbool.h>
#include <stdio.h>
#include "Geometry.h"

///////////////// Point ///////////////////////
typedef union
{
	float coords[2];
	struct
	{
		float x;
		float y;
	};
}Point;

void Point_Print(Point const* p);
bool Point_Equals(Point const* p1, Point const* p2);

#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))

Point Point_MIN(Point const* p1, Point const* p2);
Point Point_MAX(Point const* p1, Point const* p2);
Point Point_Add(Point const* p1, Point const* p2);

///////////////// Rect ///////////////////////

typedef union
{
	float arr[4];
	struct
	{
		float x;
		float y;
		float width;
		float height;
	};
	struct
	{
		Point TL;
		Point WH;
	};
}Rect;

void Rect_Print(Rect const* r);
Point Rect_BR(Rect const * r);
Point Rect_Center(Rect const * r);
Rect Rect_InitFromPoints(Point const * TL, Point const* BR);
bool Rect_IsValid(Rect const* r);


Rect Rect_GuessWhat(Rect const* r1, Rect const* r2);