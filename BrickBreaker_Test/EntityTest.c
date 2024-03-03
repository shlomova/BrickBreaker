#include "Entity.h"
#include "TestDefs.h"
#include "EntityTest.h"
#include <string.h>
#include <stdlib.h>

bool Entity_areEqual(Entity * a, Entity* b)
{
	// check that both a and b are not null, 
	// or both are indeed null.
	if (!a && !b)
		return true;
	else if (!a || !b)
		return false;

	// images

	bool a_hasAnimation = NULL != a->animation;
	bool b_hasAnimation = NULL != b->animation;

	if (a_hasAnimation != b_hasAnimation)
		return false;

	if (a_hasAnimation && b_hasAnimation)
	{
		if (List_Length(a->animation) != List_Length(b->animation))
			return false;

		size_t numFrames = List_Length(a->animation);
		Link* a_frameLink = a->animation->next;
		Link* b_frameLink = b->animation->next;
		for (int i = 0; i < numFrames; i++)
		{
			CvMat* a_img = (CvMat*)a_frameLink->value;
			CvMat* b_img = (CvMat*)b_frameLink->value;
			if (false == Mat_IsEqual(a_img, b_img))
				return false;
		}
	}

	// ROI
	if (0 != memcmp(&a->ROI, &b->ROI, sizeof(a->ROI)))
		return false;

	// velocity
	if (0 != memcmp(&a->velocity, &b->velocity, sizeof(a->velocity)))
		return false;

	return true;
}

int Entity_Create_test()
{
	// Arrange
	const char* animationsRootFolder = "../Tests/Entity_Create";

	Entity expected_entity;
	expected_entity.animation = List_Create();
	CvMat frame = Mat_Create(50, 50);
	uint8_t color[] = {255, 255, 255};
	Mat_SetColor(frame, color);
	List_Insert(expected_entity.animation, frame);
	
	expected_entity.currFrame = expected_entity.animation->next;
	expected_entity.ROI.x = expected_entity.ROI.y = 0;
	expected_entity.ROI.width = expected_entity.ROI.height = 50;

	expected_entity.velocity.x = expected_entity.velocity.y = 0;

	// Act
	Entity* actual_entity = Entity_Create(animationsRootFolder);
	ASSERT(actual_entity);

	// Assert
	bool areEqual = Entity_areEqual(actual_entity,&expected_entity);

	Entity_Free(actual_entity);
	Mat_Free(frame);
	List_Free(expected_entity.animation);
	ASSERT(areEqual);
	return TEST_PASS;

}

int Entity_CreateVirtual_test()
{
	//arrange
	Entity expected_entity;
	Rect roi = { .x = 10, .y = 52, .width = 32, .height = 34 };
	expected_entity.ROI = roi;
	expected_entity.velocity.x = expected_entity.velocity.y = 0;
	expected_entity.animation = List_Create();
	expected_entity.currFrame = NULL;

	//act
	Entity* actual_entity = Entity_CreateVirtual(roi);

	//assert
	bool areEqual = Entity_areEqual(actual_entity, &expected_entity);

	Entity_Free(actual_entity);
	List_Free(expected_entity.animation);
	ASSERT(areEqual);
	return TEST_PASS;

}
int Entity_Clone_test()
{
	//arrange
	const char* animationsRootFolder = "../Tests/Entity_Create";
	Entity* expected_entity = Entity_Create(animationsRootFolder);

	//act
	Entity* actual_entity = Entity_Clone(expected_entity);

	//assert
	bool areEqual = Entity_areEqual(actual_entity, expected_entity);
	Entity_Free(expected_entity);
	Entity_Free(actual_entity);

	ASSERT(areEqual);
	return TEST_PASS;
}

int Entity_Draw_WhenNoTransparancy_test()
{
	//arrange
	const char* animationsRootFolder = "../Tests/Entity_Create";
	const char* backgroundPath = "../Tests/Entity_Draw/background.png";
	CvMat actual = Mat_Read(backgroundPath);
	Entity* entity = Entity_Create(animationsRootFolder);
	ASSERT(NULL != entity->currFrame);
	entity->ROI.x = 10;
	entity->ROI.y = 21;

	CvMat expected = Mat_Read("../Tests/Entity_Draw/entityOverBackground.png");
	
	//act
	Entity_Draw(entity, actual, false);

	//assert
	bool areEqual = Mat_IsEqual(actual, expected);
	Mat_Free(actual);
	Mat_Free(expected);
	Entity_Free(entity);

	ASSERT(areEqual);
	return TEST_PASS;
}

int Entity_Draw_WhenWithTransparancy_test()
{
	//arrange
	const char* animationsRootFolder = "../Tests/Entity_Draw/EntityWithTransparency";
	const char* backgroundPath = "../Tests/Entity_Draw/background_forTransparency.png";
	CvMat actual = Mat_Read(backgroundPath);
	Entity* entity = Entity_Create(animationsRootFolder);
	ASSERT(NULL != entity->currFrame);
	entity->ROI.x = 10;
	entity->ROI.y = 21;

	CvMat expected = Mat_Read("../Tests/Entity_Draw/entityOverBackground_WithTransparency.png");


	//act
	Entity_Draw(entity, actual, true);

	//assert
	bool areEqual = Mat_IsEqual(actual, expected);
	Mat_Free(actual);
	Mat_Free(expected);
	Entity_Free(entity);

	ASSERT(areEqual);
	return TEST_PASS;
}

int Entity_IsValid_WhenNULL_test()
{
	ASSERT(Entity_IsValid(NULL) == false);
	return TEST_PASS;
}

int Entity_IsValid_When_ROI_invalid_test()
{
	// Arrange
	Entity e;
	e.ROI.width = -1;
	// Act, Assert
	ASSERT(Entity_IsValid(&e) == false);
	return TEST_PASS;
}

int Entity_IsValid_WhenActuallyValid_test()
{
	// Arrange
	Entity e = {.ROI.width = 10, .ROI.height = 65};
	
	// Act, Assert
	ASSERT(Entity_IsValid(&e) == true);
	return TEST_PASS;
}


int Entity_Move_WhenNoAnimation_ThenMovesOnlyROI()
{
	//Arrange
	Entity e = {
		.ROI.x = 10,
		.ROI.y = 10,
		.velocity.x = 2,
		.velocity.y = -3,
		.currFrame = NULL,
		.animation = NULL
	};
	
	//Act
	Entity_Move(&e);

	//Assert
	ASSERT(e.ROI.x == 12);
	ASSERT(e.ROI.y == 7);
	return TEST_PASS;
}

int Entity_Move_WhenThereIsAnimation_ThenIteratesFrames()
{
	//Arrange
	Entity e = {
		.ROI.x = 10,
		.ROI.y = 10,
		.velocity.x = 0,
		.velocity.y = 0,
		.currFrame = NULL,
		.animation = List_Create()
	};
	
	// the animation links data is (void *)
	// it doesn't really know what it points to
	// so just make dummy variables to be placeholders
	// instead of real images:
	int first_image_dummy = 1, 
		second_image_dummy = 2;
	
	List_Insert(e.animation, &first_image_dummy);
	List_Insert(e.animation, &second_image_dummy);
	e.currFrame = e.animation->next;

	//Act
	Entity_Move(&e);
	bool is_reached_second = e.currFrame == e.animation->next->next;
	Entity_Move(&e);
	bool is_got_back_to_first = e.currFrame == e.animation->next;

	//Assert
	List_Free(e.animation);
	ASSERT(is_reached_second);
	ASSERT(is_got_back_to_first);
	return TEST_PASS;
}

int EntityTest_main()
{
	INIT_TESTS();
	RUN_TEST(Entity_Create_test);
	RUN_TEST(Entity_CreateVirtual_test);
	RUN_TEST(Entity_Clone_test);
	RUN_TEST(Entity_Draw_WhenNoTransparancy_test);
	RUN_TEST(Entity_Draw_WhenWithTransparancy_test);
	RUN_TEST(Entity_IsValid_WhenNULL_test);
	RUN_TEST(Entity_IsValid_When_ROI_invalid_test);
	RUN_TEST(Entity_IsValid_WhenActuallyValid_test);
	RUN_TEST(Entity_Move_WhenNoAnimation_ThenMovesOnlyROI);
	RUN_TEST(Entity_Move_WhenThereIsAnimation_ThenIteratesFrames);
	FINISH_TESTS();
}