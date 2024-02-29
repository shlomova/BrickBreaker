#include "Game.h"


int main()
{
	Game* game = Game_Create();
	Point brickWall_TL = { .x = 50, .y = 30 };
	size_t bricksWall_RowsCols[] = { 4, 9 };
	const char* animationsRootFolder = "../Animations";
	Game_Load(game, animationsRootFolder, bricksWall_RowsCols, brickWall_TL);

	CvMat screen = NULL;
	
	bool isGameOn = true;
	bool isWon = false;
	while (isGameOn)
	{
		if (screen)
		{
			Mat_Free(screen);
		}
		screen = Game_Draw(game);
		CvImShow("Test", screen);
		int key = CvWaitKey(50);
		
		Game_MoveNext(game);
		
		Game_DigestKeyPress(game, key);
		if (27 == key)
			isGameOn = false;
		// if ball got lost:
		// reduce number of balls left and generate a new ball.
		// if no more balls - game over, you loose.
		// as a first step, just generate a "new ball" - place the ball back in the center.
		if (game->ball->ROI.y > Mat_Height(game->background)) {
			game->ball->ROI.y = Mat_Height(game->background) * 0.7f;
			game->ball->velocity.y = -2;
			game->ballsLeft -= 1;
			if (0 >= game->ballsLeft)
			{
				isGameOn = false;
			}
		}
		
		CvPutText(screen, isWon ? " You Win !" : " You Loose... ",
			(int)(0.3f * Mat_Width(game->background)),
			(int)(0.5f * Mat_Height(game->background)),
			2, 3);
		CvImShow("Test", screen);
		// if bricks finished - game over, you win.
		if (0 == List_Length(game->bricks))
		{
			isWon = true;
			isGameOn = false;
		}
	}
	
	CvWaitKey(0);
	CvDestroyAllWindows();
	Mat_Free(screen);
	Game_Free(game);
	return 0;
}