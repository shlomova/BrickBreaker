#include "Geometry.h"
#include "TestDefs.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "GeometryTest.h"

int Point_Equals__WhenPointsAreNotEqual()
{
	// Arrange
	Point p1 = { .x = 10, .y = 45 };
	Point p2 = { .x = 10, .y = 0 };
	Point p3 = { .x = 0, .y =  45 };

	// Act, Assert
	ASSERT(false == Point_Equals(&p1, &p2));
	ASSERT(false == Point_Equals(&p1, &p3));

	return TEST_PASS;
}

int Point_Equals__WhenPointsAreEqual()
{
	// Arrange
	Point p1 = { .x = 10, .y = 45 };
	Point p2 = p1;

	// Act, Assert
	ASSERT(Point_Equals(&p1, &p2));

	return TEST_PASS ;
}

int Point_MIN__WhenBothPointsAreTheSame()
{
	// Arrange
	Point p1 = {.x = 10, .y = 45};
	Point p2 = p1;
	Point expected = p2;
	
	// Act
	Point actual = Point_MIN(&p1, &p2);

	// Assert
	ASSERT(Point_Equals(&actual, &expected));

	return TEST_PASS;
}

int Point_MIN__TakesTheSmallestFromEachCoord()
{
	// Arrange
	Point p1 = { .x = 10, .y = 5 };
	Point p2 = { .x = 9, .y = 45 };
	Point expected = { .x = 9, .y = 5 };
	
	// Act
	Point actual = Point_MAX(&p1, &p2);

	// Assert
	ASSERT(false == Point_Equals(&actual, &expected));
		
	return TEST_PASS;
}

int Point_MAX__TakesTheLargestFromEachCoord()
{
	// Arrange
	Point p1 = { .x = 10, .y = 5 };
	Point p2 = { .x = 9, .y = 45 };
	Point expected = { .x = 10, .y = 45 };
	// Act
	Point actual = Point_MAX(&p1, &p2);
	// Assert
	ASSERT(Point_Equals(&actual, &expected));

	return TEST_PASS;
}

int Point_Add__Sanity()
{
	// Arrange
	Point p1 = { .x = 10, .y = 5 };
	Point p2 = { .x = 9, .y = 45 };
	Point expected = { .x = 19, .y = 50 };
	// Act
	Point actual = Point_Add(&p1, &p2);
	// Assert
	ASSERT(Point_Equals(&actual, &expected));

	return TEST_PASS;
}

int Rect_BR__Sanity()
{
	// Arrange
	Rect r = {.x = 10, .y = 20, .width = 5, .height = 7};
	Point expected_BR = { .x = r.x + r.width, .y = r.y + r.height };

	// Act
	Point actual_BR = Rect_BR(&r);

	// Assert
	ASSERT(Point_Equals(&actual_BR, &expected_BR));

	return TEST_PASS;
}

int Rect_Center__Sanity()
{
	// Arrange
	Rect r = { .x = 10, .y = 20, .width = 10, .height = 20 };
	Point expected = { .x = r.x + r.width/2.f, .y = r.y + r.height/2.f };

	// Act
	Point actual = Rect_Center(&r);

	// Assert
	ASSERT(Point_Equals(&actual, &expected));
		
	return TEST_PASS;
}

bool Rect_Equals(Rect const* r1, Rect const* r2)
{
	return 0 == memcmp(r1, r2, sizeof(Rect));
}

int Rect_InitFromPoints__ValidCase()
{
	// Arrange
	Point TL = { 5,10 };
	Point BR = { 15,20 };
	Rect expected = { .x = 5,.y = 10,.width = 10,.height = 10 };
	// Act
	Rect actual = Rect_InitFromPoints(&TL, &BR);
	// Assert
	ASSERT(Rect_Equals(&actual, &expected));

	return TEST_PASS;
}

int Rect_InitFromPoints__NON_ValidCase()
{
	// Arrange
	Point TL = { 15,20 };
	Point BR = { 5, 10 };
	Rect expected = { .x = 15,.y = 20,.width = -10,.height = -10 };
	// Act
	Rect actual = Rect_InitFromPoints(&TL, &BR);
	// Assert
	ASSERT(Rect_Equals(&actual, &expected));
		
	return TEST_PASS;
}

int Rect_IsValid__ValidCase()
{
	// Arrange
	Rect r = { .x = 0, .y = 0, .width = 1, .height = 1 };
	bool expected = true;
	
	// Act
	bool actual = Rect_IsValid(&r);
	// Assert
	ASSERT(actual == expected);

	return TEST_PASS;
}

int Rect_IsValid__NON_ValidCase()
{
	// Arrange
	Rect r1 = { .x = 0, .y = 0, .width = 0, .height = 1 };
	Rect r2 = { .x = 0, .y = 0, .width = 1, .height = 0 };
	bool expected = false;

	// Act
	bool actual = Rect_IsValid(&r1) || Rect_IsValid(&r2);
	// Assert
	ASSERT(actual == expected);
		
	return TEST_PASS;
}

int GeometryTest_main()
{
	INIT_TESTS();
	RUN_TEST(Point_Equals__WhenPointsAreNotEqual);
	RUN_TEST(Point_Equals__WhenPointsAreEqual);
	RUN_TEST(Point_MIN__WhenBothPointsAreTheSame);
	RUN_TEST(Point_MIN__TakesTheSmallestFromEachCoord);
	RUN_TEST(Point_MAX__TakesTheLargestFromEachCoord);
	RUN_TEST(Point_Add__Sanity);
	RUN_TEST(Rect_BR__Sanity);
	RUN_TEST(Rect_Center__Sanity);
	RUN_TEST(Rect_InitFromPoints__ValidCase);
	RUN_TEST(Rect_InitFromPoints__NON_ValidCase);
	RUN_TEST(Rect_IsValid__ValidCase);
	RUN_TEST(Rect_IsValid__NON_ValidCase);
	FINISH_TESTS();
}

