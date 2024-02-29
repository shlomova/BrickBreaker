#include "FileUtils.h"
#include "TestDefs.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "FileUtilsTest.h"

int isFileExists__WhenItDoesnt_ThenReturnsFalse()
{
	// Arrange, Act, Assert
	ASSERT(false == isFileExists("./file/that/does/not/exist.txt"));
	return TEST_PASS;
}

int isFileExists__WhenItActuallyDoes_ThenReturnsTrue()
{
	// Arrange
	const char* file_that_exists_path = "../Tests/FileUtils/existing_file.txt";

	// Act
	// Assert
	ASSERT(true == isFileExists(file_that_exists_path));
	return TEST_PASS;
}

int isFileExists__WhenInputIsNULL_ThenReturnsFalse()
{
	// Arrange, Act, Assert
	ASSERT(false == isFileExists(NULL));
	return TEST_PASS;
}

int concatPaths_WhenFirst_DoesNOT_EndWithBackSlash_ThenAddsIt()
{
	// Arrange
	const char* expected = "root/sub_path";

	// Act
	char* actual = concatPaths("root", "sub_path");

	// Assert
	ASSERT(actual);
	bool isOk = 0 == strcmp(actual, expected);
	free(actual);
	ASSERT(isOk);
	return TEST_PASS;
}

int concatPaths_WhenFirstEndsWithBackSlash_ThenDoesntAddIt()
{
	// Arrange
	const char* expected = "root\\sub_path";
	
	// Act
	char * actual = concatPaths("root\\", "sub_path");

	// Assert
	ASSERT(actual);
	bool isOk = 0 == strcmp(actual, expected);
	free(actual);
	ASSERT(isOk);
	return TEST_PASS;
}

int concatPaths_WhenFirstEndsWithSlash_ThenDoesntAddIt()
{
	// Arrange
	const char* expected = "root/sub_path";

	// Act
	char* actual = concatPaths("root/", "sub_path");

	// Assert
	ASSERT(actual);
	bool isOk = 0 == strcmp(actual, expected);
	free(actual);
	ASSERT(isOk);
	return TEST_PASS;
}


int getFramePath_Sanity()
{
	// Arrange
	const char* expected = "root/45.png";

	// Act
	char * actual = getFramePath("root", 45);

	// Assert
	ASSERT(actual);
	bool isOk = 0 == strcmp(actual, expected);
	free(actual);
	ASSERT(isOk);
	return TEST_PASS;
}

int countAnimationFrames_WhenOnFolderWithoutFrames_ThenReturnsZero()
{
	// Arrange, Act
	size_t count = countAnimationFrames("../Tests");
	
	// Assert
	ASSERT(0 == count);
	return TEST_PASS;
}

int countAnimationFrames_WhenOnFolderWithFrames_ThenReturnsCorrectCount()
{
	// Arrange, Act
	size_t count = countAnimationFrames("../Tests/DummyFramesFolder");

	// Assert
	ASSERT(7 == count);
	return TEST_PASS;
}

int FileUtilsTest_main()
{
	INIT_TESTS();
	RUN_TEST(isFileExists__WhenItDoesnt_ThenReturnsFalse);
	RUN_TEST(isFileExists__WhenItActuallyDoes_ThenReturnsTrue);
	RUN_TEST(isFileExists__WhenInputIsNULL_ThenReturnsFalse);
	RUN_TEST(concatPaths_WhenFirst_DoesNOT_EndWithBackSlash_ThenAddsIt);
	RUN_TEST(concatPaths_WhenFirstEndsWithBackSlash_ThenDoesntAddIt);
	RUN_TEST(concatPaths_WhenFirstEndsWithSlash_ThenDoesntAddIt);
	RUN_TEST(getFramePath_Sanity);
	RUN_TEST(countAnimationFrames_WhenOnFolderWithoutFrames_ThenReturnsZero);
	RUN_TEST(countAnimationFrames_WhenOnFolderWithFrames_ThenReturnsCorrectCount);
	FINISH_TESTS();
}

