#include "Entity.h"
#include "core.h"
#include "FileUtils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void fillInFrames(LinkedList framesList, const char* animationFolder)
{
    size_t count_frames = countAnimationFrames(animationFolder);
    if (count_frames == 0) return;

    for (size_t frameIdx = 1; frameIdx <= count_frames; frameIdx++) {
        char* filePath = getFramePath(animationFolder, frameIdx);
        if (!filePath) {
            printf("Error: Unable to get file path for frame %zu\n", frameIdx);
            continue; 
        }

        void* frameData = Mat_Read(filePath); // MAT_Free
        if (!frameData) {
            printf("Error: Failed to read frame %zu\n", frameIdx);
            free(filePath);
            continue; 
        }

        List_ErrorCodes result = List_Insert(framesList, frameData);
        if (result != SUCCESS) {
            printf("Error: Failed to insert frame %zu into the list\n", frameIdx);
            free(filePath); 
            break;
        }

        free(filePath); 
    }
}


Entity* Entity_Create(const char* animationsFolder)
{
    Entity* entity = (Entity*)malloc(sizeof(Entity));
    if (!entity)
        return NULL;

    // init pointers to NULL for marking they weren't yet set:
    entity->animation = NULL;
    entity->currFrame = NULL;


    // Create and fill in entity->animation
    entity->animation = List_Create();
    if (!entity->animation) {
        free(entity);
        return NULL;
    }

    fillInFrames(entity->animation, animationsFolder);

    // init entity->currFrame to point to the first link in entity->animation.
    // and handle the case when entity->animation is Empty!
    if (entity->animation->next != NULL) 
        {
            entity->currFrame = entity->animation->next;

            // init entity->ROI to (0,0,W,H). 
            // and handle the case when entity->animation is Empty!
            float w = (float) Mat_Width(entity->currFrame->value);
            float h = (float) Mat_Height(entity->currFrame->value);
            entity->ROI = (Rect){ .TL = {0,0}, .WH = {w,h} };
        }
    // init entity->velocity to be zero in each direction.
    entity->velocity = (Point){ .coords = {0,0} };
    
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
