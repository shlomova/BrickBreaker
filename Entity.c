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
    entity->currFrame = entity->animation->next;
    if (entity->animation->next != NULL) 
        {
            // init entity->ROI to (0,0,W,H). 
            // and handle the case when entity->animation is Empty!
            float w = (float) Mat_Width(entity->currFrame->value);
            float h = (float) Mat_Height(entity->currFrame->value);
            entity->ROI = (Rect){ .TL = {0,0}, .WH = {w,h} };
        }
    else {
        entity->ROI = (Rect){ .TL = {0,0}, .WH = {0,0} };
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

    // entity->animation must be a valid (yet empty) list.
    entity->animation = List_Create();
    if (!entity->animation) {
        free(entity);
        return NULL;
    }
    
    // what to do with entity->currFrame ?
    // -> currFrame remains NULL since there's no animation.
     
    // init entity->ROI , that's what this Entity is made for :)
    entity->ROI = roi;


    // init entity->velocity to be zero.
    entity->velocity = (Point){ .coords = {0,0} };

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
    // first free the pointed images, then free the list itself.
    for (Link* l = framesList->next; l != NULL; l = l->next) {
        Mat_Free(l->value);
    }

    List_Free(framesList);

}

// Important! freeFrames before this:
void Entity_Free(Entity* entity)
{
    // free the animation, then the entity itself.
    freeFrames(entity->animation);
    free(entity);
}

void Entity_Draw(Entity const* entity, CvMat background, bool isWithTransparency)
{
    if (entity == NULL || entity->currFrame == NULL || entity->currFrame->value == NULL)
    {
        // Invalid entity or frame, cannot draw
        return;
    }

    int TL[2]; // Array to hold integer coordinates so do casting
    TL[0] = (int)entity->ROI.TL.x; 
    TL[1] = (int)entity->ROI.TL.y; 

    if (isWithTransparency == false)
        Mat_CopyTo(entity->currFrame->value, background, TL);
    else
        Mat_CopyTo_WithTransparency(entity->currFrame->value, background,TL);
}

bool Entity_IsValid(Entity const* entity)
{
    if (!entity)
        return false;

    return Rect_IsValid(&entity->ROI);
}

void Entity_Move(Entity* entity)
{
    if (entity == NULL) return;

    // Update ROI top-left coordinates by adding velocity
    entity->ROI.x += entity->velocity.x;
    entity->ROI.y += entity->velocity.y;

    if (entity->animation == NULL || entity->animation->next == NULL) {
        return;
    }
    // Move to the next frame in the animation
    if (entity->currFrame == NULL || entity->currFrame->next == NULL) {
        entity->currFrame = entity->animation->next;
    }
    else {
        entity->currFrame = entity->currFrame->next;
    }


}
