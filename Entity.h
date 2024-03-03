#pragma once
#include "LinkedList.h"
#include "core.h"
#include "Geometry.h"

typedef struct {
	/// <summary>
	/// Linked list of images (CvMat) that form the Entity's animation.
	/// Each such link is also called a Frame. 
	/// </summary>
	LinkedList animation;
	
	/// <summary>
	/// A Pointer to the Link in "animation" that's currently presented.
	/// </summary>
	Link* currFrame;

	/// <summary>
	/// ROI stands for Reagion Of Interest. 
	/// it's the Entity's location in the game.
	/// </summary>
	Rect ROI;

	/// <summary>
	/// speed of movement of the Entity in X and Y directions
	/// </summary>
	Point velocity;
	
}Entity;

/// <summary>
/// Fills in the framesList with images 1.png, 2.png, ... from the animationFolder.
/// use:
/// countAnimationFrames and getFramePath in FileUtils.h, 
/// Mat_Read in core.c, 
/// List_Insert in LinkedList.h
/// </summary>
/// <param name="framesList">List to be filled</param>
/// <param name="animationFolder">Folder with images 0.png, 1.png, ... </param>
void fillInFrames(LinkedList framesList, const char* animationFolder);

/// <summary>
/// Allocates and initializes an Entity with animation taken from
/// animationsFolder (with images 1.png, 2.png, ...).
/// The created Entity's ROI top left corner is placed at x=y=0
/// In case where animationsFolder does not contain images returns an
/// Entity with animation of length zero.
/// </summary>
/// <param name="animationsFolder">Path of images folder</param>
/// <returns>An instance of Entity</returns>
Entity* Entity_Create(const char* animationsFolder);

/// <summary>
/// Allocates and initializes an Entity, which has no animation 
/// (animation length is zero),
/// Yet occupies some ROI. Therefore it's called "Virtual" 
/// - since it's not drawable, yet present.
/// </summary>
/// <param name="roi">ROI to be occupied by this virtual entity</param>
/// <returns></returns>
Entity* Entity_CreateVirtual(Rect roi);

/// <summary>
/// Creates a deep copy of an Entity (Clones all the animation)
/// </summary>
/// <param name="other"></param>
/// <returns></returns>
Entity* Entity_Clone(Entity const* other);

/// <summary>
/// Frees the Entity. Also takes care of freeing the animation correctly
/// </summary>
/// <param name="entity"></param>
void Entity_Free(Entity* entity);


/// <summary>
/// Draws Entity on the background, starting from entity->ROI top left,
/// with or without transparency (CopyTo or CopyTo_WithTransparency).
/// </summary>
/// <param name="entity">The Entity to draw</param>
/// <param name="background">The image to draw it on</param>
void Entity_Draw(Entity const* entity, CvMat background, bool isWithTransparency);

/// <summary>
/// True if entity not null and ROI width/height are positive.
/// </summary>
/// <param name="entity"></param>
/// <returns></returns>
bool Entity_IsValid(Entity const* entity);

/// <summary>
/// Moves entity->currFrame to the next one (or, if reached 
/// the end of the list - back the the first one).
/// Also, updates entity->ROI.TL by adding to it the entity->velocity.
/// </summary>
void Entity_Move(Entity* entity);