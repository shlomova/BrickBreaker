#include "EntityTest.h"
#include "GeometryTest.h"
#include "TestDefs.h"
#include "FileUtilsTest.h"
int main()
{
	INIT_TESTS();
	RUN_TESTS_SUITE(GeometryTest_main);
	//RUN_TESTS_SUITE(EntityTest_main);
	//RUN_TESTS_SUITE(FileUtilsTest_main);
	PRINT_ALL_TESTS_RES();
	FINISH_TESTS();
}