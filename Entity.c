#include "Entity.h"
#include "core.h"
#include "FileUtils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/// <summary>
/// Fills in the framesList with images 0.png, 1.png, ... from the animationFolder.
/// use:
/// countAnimationFrames, getFramePath, Mat_Read, List_Insert
/// </summary>
/// <param name="framesList">List to be filled</param>
/// <param name="animationFolder">Folder with images 0.png, 1.png, ... </param>
void fillInFrames(LinkedList framesList, const char* animationFolder)
{
    // TODO ...
}

Entity* Entity_Create(const char* animationsFolder)
{
    Entity* entity = (Entity*)malloc(sizeof(Entity));
    if (!entity)
        return NULL;
    
    // init pointers to NULL for marking they weren't yet set:
    entity->animation = NULL;
    entity->currFrame = NULL;


    // TODO: Create and fill in entity->animation
    // entity->animation = ... 
    // ...

    // TODO: init entity->currFrame to point to the first link in entity->animation.
    // Remember to handle the case when entity->animation is Empty!
    // ...

    // TODO: init entity->ROI to (0,0,W,H). 
    // Remember to handle the case when entity->animation is Empty!
    // ...

    // TODO: init entity->velocity to be zero in each direction.
    // ...
    
    return entity;
}

Entity* Entity_CreateVirtual(Rect roi)
{
    Entity* entity = (Entity*)malloc(sizeof(Entity));
    if (!entity)
        return NULL;

    // init pointers to NULL for marking they weren't yet set:
    entity->animation = NULL;
    entity->currFrame = NULL;

    // TODO: entity->animation must be a valid (yet empty) list.
    // ...
    
    // TODO: what to do with entity->currFrame ?

    // TODO: init entity->ROI , that's what this Entity is made for :)
    
    // TODO: init entity->velocity to be zero.

    return entity;
}

Entity* Entity_Clone(const Entity* other)
{
    Entity* entity = (Entity*)malloc(sizeof(Entity));
    if (!entity)
        return NULL;
    
    *entity = *other;
    
    if (!other->animation) // shouldn't happen, but must check.
        return entity;

    // Create a deep copy of the animation:
    entity->animation = List_Create();
    
    for (Link* othersFrame = other->animation->next;
        othersFrame != NULL;
        othersFrame = othersFrame->next)
    {
        CvMat image = othersFrame->value;
        CvMat image_clone = Mat_Clone(image);
        List_Insert(entity->animation, image_clone);
    }

    if (entity->animation->next)
        entity->currFrame = entity->animation->next;
    else
        entity->currFrame = NULL;

    return entity;
}

/// <summary>
/// Free a list of frames - where every link points to an image.
/// </summary>
/// <param name="framesList"></param>
void freeFrames(LinkedList framesList)
{
    // TODO: first free the pointed images, then free the list itself.
}

// TODO: Important! implement freeFrames before you implement this:
void Entity_Free(Entity* entity)
{
    // TODO: free the animation, then the entity itself.
}

void Entity_Draw(Entity const* entity, CvMat background, bool isWithTransparency)
{
    // TODO
}

bool Entity_IsValid(Entity const* entity)
{
    if (!entity)
        return false;

    return entity->ROI.width > 0
        && entity->ROI.height > 0;
}

void Entity_Move(Entity* entity)
{
    // TODO
}
