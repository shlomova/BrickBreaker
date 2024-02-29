#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "FileUtils.h"

// hint: if fopen works - file exist.
bool isFileExists(const char* filepath)
{
    return false;
}

char* concatPaths(const char* root, const char* toAppend)
{
    // TODO: check if root path ends with \ or / and save it into a variable:
    bool isRequiredTrailingSlash = false;

    // TODO: calculate length of the concatinated path:
    // hint: output length = strlen + strlen [sometimes, + 1]
    size_t concatPathLength = 0;
    if (0 == concatPathLength)
        return NULL;

    char* concatPath = (char*)malloc(concatPathLength);
    if (!concatPath)
        return NULL;

    // TODO: use strcpy and strcat to construct the output:
    // ...
    //

    return concatPath;
}

char* getFramePath(const char* animationFolder, int frameIdx)
{
    char frameIdxStr[30] = { 0 };
    _itoa(frameIdx, frameIdxStr, 10);
    strcat(frameIdxStr, ".png");
    return concatPaths(animationFolder, frameIdxStr);
}

size_t countAnimationFrames(const char* animationFolder)
{
    size_t frameIdx = 0;
    bool isFrameExist = true;
    while (isFrameExist)
    {
        frameIdx++;
        char* framePath = getFramePath(animationFolder, (int)frameIdx);
        isFrameExist = isFileExists(framePath);
        free(framePath);
    }
    return frameIdx - 1;
}
