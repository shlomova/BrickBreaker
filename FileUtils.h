#pragma once
#include <stdbool.h>
/// <summary>
/// returns true if file exists, otherwise false.
/// </summary>
bool isFileExists(const char* filepath);

/// <summary>
/// allocates a new path which is a concatination of root and toAppend.
/// Look in the unit tests for more information (Ctrl+Shift+F)
/// </summary>
char* concatPaths(const char* root, const char* toAppend);

/// <summary>
/// Concatinate base folder with frameIdx + ".png"
/// </summary>
char* getFramePath(const char* animationFolder, int frameIdx);

/// <summary>
/// For folder with animation images numbered 0.png, 1.png, ... count how many
/// of those are present in that folder.
/// </summary>
size_t countAnimationFrames(const char* animationFolder);
