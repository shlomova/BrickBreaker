#include <stdbool.h>
#include <stdio.h>
#include "Geometry.h"

///////////////// Point ///////////////////////

void Point_Print(Point const* p)
{
	printf("[P->x=%f, P->y=%f]\n", p->x, p->y);
}

bool Point_Equals(Point const* p1, Point const* p2)
{
	return (p1->x == p2->x) && (p1->y == p2->y);
}

Point Point_Add(Point const* p1, Point const* p2)
{
	Point result = { p1->x + p2->x, p1->y + p2->y };
	return result;
}

Point Point_MIN(Point const* p1, Point const* p2)
{
	// hint: use the MIN macro in Geometry.h
	Point result = { MIN(p1->x, p2->x), MIN(p1->y, p2->y) };
	return result;
}

Point Point_MAX(Point const* p1, Point const* p2)
{
	// hint: use the MAX macro in Geometry.h
	Point result = { MAX(p1->x, p2->x), MAX(p1->y, p2->y) };
	return result;
}

///////////////// Rect ///////////////////////
// BR = Bottom Right
Point Rect_BR(Rect const* r) {
	Point br = Point_Add(&(r->TL), &(r->WH));
	return br;
}

Point Rect_Center(Rect const* r)
{
	Point center = { .x = r->x + r->width / 2.f, .y = r->y + r->height / 2.f };
	return center;
}

Rect Rect_InitFromPoints(Point const* TL, Point const* BR)
{
	Rect result;

	// copy top-left corner
	result.TL = *TL;

	// Calculate width and height
	result.width = BR->x - TL->x;
	result.height = BR->y - TL->y;

	return result;
}

bool Rect_IsValid(Rect const* r)
{
	return r->width > 0 && r->height > 0;
}

Rect Rect_CombineAndBound(Rect const* r1, Rect const* r2)
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