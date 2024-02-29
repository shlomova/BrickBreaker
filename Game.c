#include "Game.h"

LinkedList LoadBrickTypes(const char* animationsRootFolder)
{
    LinkedList brickTypes = List_Create();

    char* bricksRootFolder = concatPaths(animationsRootFolder, "Bricks");
    int brickIdx = 1;
    bool stillValid = true;
    char brickIdxStr[30] = { 0 };

    while (stillValid)
    {
        _itoa(brickIdx, brickIdxStr, 10);
        char* brickFolder = concatPaths(bricksRootFolder, brickIdxStr);
        Entity* brick = Entity_Create(brickFolder);
        free(brickFolder);

        if (Entity_IsValid(brick))
        {
            List_Insert(brickTypes, brick);
            brickIdx++;
        }
        else
        {
            Entity_Free(brick);
            stillValid = false;
        }
    }
    free(bricksRootFolder);

    return brickTypes;
}

Game* Game_Create()
{
    Game* g = calloc(1, sizeof(Game));
    if (g)
        return g;
    else
        return NULL;
}

void EntitiesList_Free(LinkedList entitiesList)
{
    for (Link* l = entitiesList->next;
        l != NULL; l = l->next)
    {
        Entity* e = l->value;
        Entity_Free(e);
    }
    List_Free(entitiesList);
}


void Game_Free(Game* game)
{
    if (game->background)
        Mat_Free(game->background);
    if (game->ball)
        Entity_Free(game->ball);
    if (game->borders)
    {
        EntitiesList_Free(game->borders);
    }
    if (game->bricks)
    {
        EntitiesList_Free(game->bricks);
    }
    if (game->brickTypes)
    {
        EntitiesList_Free(game->brickTypes);
    }
    if (game->racketSingleton)
    {
        // This will free racket image as well:
        EntitiesList_Free(game->racketSingleton);
    }
}

void Game_Load(Game* game, const char* animationsRootFolder,
    size_t bricksWall_RowsCols[2],
    Point brickWall_TL)
{
    // TODO: Check if required rows*cols = 0 - Game_Free & return
    {
        char* backgroundFile = concatPaths(animationsRootFolder, "Background.png");
        game->background = Mat_Read(backgroundFile);
        free(backgroundFile);
        // TODO: Check if no background - Game_Free & return

        // Create "virtual" entities for marking borders:
        Rect leftBorderROI = { .x = -10, .y = 0, .width = 10, .height = (float)Mat_Height(game->background) };
        Rect rightBorderROI = { .x = (float)Mat_Width(game->background), .y = 0, .width = 10, .height = (float)Mat_Height(game->background) };
        Rect topBorderROI = { .x = 0, .y = -10, .width = (float)Mat_Width(game->background), .height = 10 };
        game->borders = List_Create();
        List_Insert(game->borders, Entity_CreateVirtual(leftBorderROI));
        List_Insert(game->borders, Entity_CreateVirtual(rightBorderROI));
        List_Insert(game->borders, Entity_CreateVirtual(topBorderROI));
        // TODO: Check if any of the above borders is null - Game_Free & return.
    } {
        char* racketRootFolder = concatPaths(animationsRootFolder, "Racket");
        game->racket = Entity_Create(racketRootFolder);
        free(racketRootFolder);
        // TODO: Check if racket is null / invalid - Game_Free & return
        game->racket->ROI.x = Mat_Width(game->background) / 2 - game->racket->ROI.width / 2;
        game->racket->ROI.y = Mat_Height(game->background) * 0.9f;
        game->racketSingleton = List_Create();
        List_Insert(game->racketSingleton, game->racket);
    } {
        char* ballRootFolder = concatPaths(animationsRootFolder, "Ball");
        game->ball = Entity_Create(ballRootFolder);
        free(ballRootFolder);
        // TODO: Check if ball is null / invalid - Game_Free & return
        game->ball->ROI.x = Mat_Width(game->background) / 2 - game->ball->ROI.width / 2;
        game->ball->ROI.y = Mat_Height(game->background) * 0.7f;
        game->ball->velocity.y = -2;
        game->ball->velocity.x = -2;
        game->ballsLeft = 3;
    }
    game->brickTypes = LoadBrickTypes(animationsRootFolder);
    // TODO: Check if brick types empty / null - Game_Free & return

    game->bricks = List_Create();
    // TODO: Check if bricks empty - Game_Free & return

    Link* currBrickType = game->brickTypes->next;
    for (int row = 0; row < bricksWall_RowsCols[0]; row++)
    {
        for (int col = 0; col < bricksWall_RowsCols[1]; col++)
        {
            if (!currBrickType)// reached end of list
                currBrickType = game->brickTypes->next;

            Entity* brickType = (Entity*)currBrickType->value;
            Entity* brick = Entity_Clone(brickType);
            brick->ROI.x = brickWall_TL.x + col * brick->ROI.width;
            brick->ROI.y = brickWall_TL.y + row * brick->ROI.height;
            List_Insert(game->bricks, brick);

            currBrickType = currBrickType->next;
        }
    }
}

Link* FindCollision(Rect mineRoi, LinkedList otherEntities)
{
    for (Link* entityLink = otherEntities->next;
        entityLink != NULL;
        entityLink = entityLink->next)
    {
        Entity* other = entityLink->value;
        Rect what = Rect_CombineAndBound(&mineRoi, &other->ROI);
        if (Rect_IsValid(&what))
            return entityLink;
    }

    return NULL;
}

Link* Entity_HandleCollision(Entity* me, LinkedList otherEntities)
{
    Rect currRoi = me->ROI;
    Rect nextRoi = currRoi;
    nextRoi.TL = Point_Add(&nextRoi.TL, &me->velocity);

    Link* colliding_entity_link = FindCollision(nextRoi, otherEntities);
    if (colliding_entity_link)
    {
        Entity* colliding_entity = colliding_entity_link->value;
        Rect what = Rect_CombineAndBound(&nextRoi, &colliding_entity->ROI);
        bool isVerticalCollision = what.height > what.width;
        if (isVerticalCollision)
            me->velocity.x *= -1;
        else
            me->velocity.y *= -1;
    }

    me->ROI.TL = Point_Add(&me->ROI.TL, &me->velocity);
    return colliding_entity_link;
}

void Game_MoveNext(Game* game)
{
    Link* brickToBreak_link = Entity_HandleCollision(game->ball, game->bricks);
    if (brickToBreak_link)
    {
        Entity* brickToBreak = brickToBreak_link->value;
        Entity_Free(brickToBreak);
        List_Remove(game->bricks, brickToBreak_link, true);
    }

    Entity_HandleCollision(game->ball, game->borders);
    if (Entity_HandleCollision(game->racket, game->borders))
    {
        // special case:
        game->racket->velocity.x *= 0.5;
    }

    if (Entity_HandleCollision(game->ball, game->racketSingleton))
    {
        // special case:
        Point ball_center = Rect_Center(&game->ball->ROI);
        Point racket_center = Rect_Center(&game->racket->ROI);
        game->ball->velocity.x = (ball_center.x - racket_center.x) / 50;
    }

    Entity_Move(game->ball);
    Entity_Move(game->racket);
    // racket velocity should reduct over time:
    game->racket->velocity.x *= 0.9f;

    for (Link* l = game->bricks->next; l != NULL; l = l->next)
        Entity_Move(l->value);
}

void Game_DigestKeyPress(Game* game, int key)
{
    switch (key)
    {
    case 'a': game->racket->velocity.x = MAX(-1 + game->racket->velocity.x, -10);  break;
    case 'd': game->racket->velocity.x = MIN(+1 + game->racket->velocity.x, 10); break;
    default:
        break;
    }
}

CvMat Game_Draw(Game* game)
{
    CvMat background = Mat_Clone(game->background);
    // Check if not background
    for (Link* brickEntityLink = game->bricks->next;
        brickEntityLink != NULL;
        brickEntityLink = brickEntityLink->next)
    {
        Entity_Draw(brickEntityLink->value, background, false);
    }
    Entity_Draw(game->ball, background, true);
    Entity_Draw(game->racket, background, false);
    char ballsLeft_txt[5] = { 0 };
    _itoa(game->ballsLeft, ballsLeft_txt, 10);
    CvPutText(background, ballsLeft_txt,
        0,
        50,
        2, 3);
    return background;
}