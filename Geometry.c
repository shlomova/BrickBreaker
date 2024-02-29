#include <stdbool.h>
#include <stdio.h>
#include "Geometry.h"

void Point_Print(Point const* p)
{
	printf("[P->x=%f, P->y=%f]\n", p->x, p->y);
}

// TODO:
bool Point_Equals(Point const* p1, Point const* p2)
{
	return false;
}

Point Point_Add(Point const* p1, Point const* p2)
{
	Point result = { 0, 0 };
	return result;
}

Point Rect_BR(Rect const* r) {
	Point br = { 0, 0};
	return br;
}

Point Rect_Center(Rect const* r)
{
	Point center = { 0, 0};
	return center;
}

Rect Rect_InitFromPoints(Point const* TL, Point const* BR)
{
	Rect result = {  0, 0, 0, 0 };
	return result;
}

bool Rect_IsValid(Rect const* r)
{
	return r->width > 0 && r->height > 0;
}

Point Point_MIN(Point const* p1, Point const* p2)
{
	// hint: use the MIN macro in Geometry.h
	Point result = { 0, 0};
	return result;
}

Point Point_MAX(Point const* p1, Point const* p2)
{
	// hint: use the MAX macro in Geometry.h
	Point result = { 0, 0 };
	return result;
}

Rect Rect_GuessWhat(Rect const* r1, Rect const* r2)
{
	Point TL = Point_MAX(&r1->TL, &r2->TL);
	
	Point BR_r1 = Rect_BR(r1);
	Point BR_r2 = Rect_BR(r2);

	Point BR = Point_MIN(&BR_r1, &BR_r2);

	return Rect_InitFromPoints(&TL, &BR);
}
void Rect_Print(Rect const* r)
{
	printf("[r->x=%f, r->y=%f, r->width=%f, height=%f] Valid? %s\n", r->x, r->y, r->width, r->height, Rect_IsValid(r) ? "YES" : "NO");
}