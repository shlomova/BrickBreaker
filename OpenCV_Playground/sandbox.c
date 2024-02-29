#include "core.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

void Create_Mat_Set_Color()
{
	// Create a new image:
	CvMat m = Mat_Create(500, 500);
	// Choose color:
	uint8_t color[] = { 10, 150, 152 };
	// Set color to image:
	Mat_SetColor(m, color);
	// Write image to disc:
	Mat_Write("test.png", m);
	// Free image:
	Mat_Free(m);

	// No need to free color - 
	// it's on the stack, not on 
	// the heap (we didn't use malloc)
}

void Read_Mat_PutText()
{
	// Read an image from disc:
	CvMat m = Mat_Read("../Animations/Background.png");
	// Write something on the image:
	CvPutText(m, "Hi did you miss me?", 50, 150, 2, 2);
	// Write image to disc:
	Mat_Write("test.png", m);
	// Free image:
	Mat_Free(m);
}

void Read_Clone_Mat_PutText()
{
	// Read an image from disc:
	CvMat m = Mat_Read("../Animations/Background.png");
	// shallow copy - just another pointer to the same instance...
	CvMat m_shallow_copy = m;
	// deep copy - an entirely different instance
	CvMat m_deep_copy = Mat_Clone(m);
	// Write something on the shallow copy:
	CvPutText(m_shallow_copy, "shallow copy", 50, 150, 2, 2);
	// Write something on the deep copy:
	CvPutText(m_deep_copy, "deep copy", 50, 150, 2, 2);
	// Write original image to disc:
	Mat_Write("original.png", m);
	// Write shallow copy to disc:
	Mat_Write("shallow.png", m_shallow_copy);
	// Write deep copy to disc:
	Mat_Write("deep.png", m_deep_copy);
	// Free image:
	Mat_Free(m);
	Mat_Free(m_deep_copy);
}

void CopyTo_Simple()
{
	// Open the ball image in paint.net. do you see it has
	// transparent background ? great! now read on.
	CvMat ball = Mat_Read("../Animations/Ball/1.png");
	CvMat forest = Mat_Read("../Animations/Background.png");

	int TopLeft[] = { 50, 50 };
	Mat_CopyTo(ball, forest, TopLeft);

	// Open the outcome - the ball's background
	// when copied onto the forest image became.. white!
	// why? because that's a simple copy. it's much faster
	// than CopyTo_WithTransparency, but it doesn't take 
	// transparency into account.
	Mat_Write("overlayed.png", forest);
}

void CopyTo_WithTransparency()
{
	// Open the ball image in paint.net. do you see it has
	// transparent background ? great! now read on.
	CvMat ball = Mat_Read("../Animations/Ball/1.png");
	CvMat forest = Mat_Read("../Animations/Background.png");

	int TopLeft[] = { 50, 50 };
	Mat_CopyTo_WithTransparency(ball, forest, TopLeft);

	Mat_Write("overlayed.png", forest);
}

void ShowingImages_SameWindow()
{
	CvMat m = Mat_Create(500, 500);
	uint8_t color[] = { 10, 150, 152 };

	const char* windowName = "Look at me!";
	char i_str[50] = { 0 };
	int delay_ms = 1000; // 1000 milliseconds = 1 second.
	for (int i = 0; i < 10; i++)
	{
		color[0] = 25 * i;
		Mat_SetColor(m, color);
		_itoa(i, i_str, 10);
		CvPutText(m, i_str, 100, 100, 2, 3);
		// Creates a new GUI window,
		// or uses an existing one - if 
		// exists with the given name.
		CvImShow(windowName, m);
		// must be called after CvImShow
		// for allowing the window thread
		// to start. though it's enough
		// to wait 1 millisec.
		// see function documentation:
		CvWaitKey(delay_ms);
	}
	Mat_Free(m);
	
	// Closes all open GUI windows:
	CvDestroyAllWindows();
}

void ShowingImages_SmallDelay_ProcessingKeys()
{
	CvMat m = Mat_Create(500, 500);
	uint8_t color[] = { 10, 150, 152 };

	const char* windowName = "Look at me!";
	
	char single_char_null_terminated_str[] = { ' ', '\0' };
	int delay_ms = 10;
	bool shouldExit = false;
	int frame_index = 0;
	while (!shouldExit)
	{
		for (int c = 0; c < 3; c++)
		{
			int curr_color_channel = (c * frame_index) % (255 * 2);
			color[c] = 
				curr_color_channel <= 255 
				? curr_color_channel
				: 255 * 2 - curr_color_channel;
		}
		frame_index++;

		Mat_SetColor(m, color);
		CvPutText(m, single_char_null_terminated_str, 100, 100, 2, 3);

		CvImShow(windowName, m);
		int key = CvWaitKey(delay_ms);
		switch (key)
		{
		case 27: // ESC key code
			shouldExit = true;
			break;
		case -1: // Nothing was pressed
			break;
		default: // something was pressed, which is not esc:
			single_char_null_terminated_str[0] = key % 255;
			break;
		}
	}
	Mat_Free(m);

	// Closes all open GUI windows:
	CvDestroyAllWindows();
}

void ShowingImages_BlockingDelay()
{
	CvMat m = Mat_Create(500, 1000);
	uint8_t color[] = { 200, 10, 10 };

	const char* windowName = "Look at me!";

	bool shouldExit = false;
	Mat_SetColor(m, color);
	CvPutText(m, "Press something!", 100, 100, 2, 3);
	CvImShow(windowName, m);
	// Wait forever till a key is pressed:
	int key = CvWaitKey(0);
	char single_char_null_terminated_str[] = { key, '\0' };
	Mat_SetColor(m, color);
	CvPutText(m, "Great! you've pressed", 100, 100, 2, 3);
	CvPutText(m, single_char_null_terminated_str, 100, 160, 2, 3);
	CvPutText(m, "Press any key to exit", 100, 250, 2, 3);
	CvImShow(windowName, m);
	// Wait forever, again, till a key is pressed:
	key = CvWaitKey(0);

	// Closes all open GUI windows:
	CvDestroyAllWindows();
	Mat_Free(m);

}

int main()
{
	int example_idx = 0;
	printf("What example to run (1-7)?\n");
	scanf("%d", &example_idx);
	switch (example_idx)
	{
	case 1: Create_Mat_Set_Color(); break;
	case 2: Read_Mat_PutText(); break;
	case 3: Read_Clone_Mat_PutText(); break;
	case 4: CopyTo_Simple(); break;
	case 5: CopyTo_WithTransparency(); break;
	case 6: ShowingImages_SameWindow(); break;
	case 7: ShowingImages_SmallDelay_ProcessingKeys(); break;
	case 8: ShowingImages_BlockingDelay(); break;

	default: printf("Unknown example idx\n"); break;
	}

	return 0;
}