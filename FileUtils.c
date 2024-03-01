#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "FileUtils.h"

// hint: if fopen works - file exist.
bool isFileExists(const char* filepath)
{
    if (filepath == NULL) return false;

    FILE* dstFile = fopen(filepath, "r");
    if (dstFile != NULL) {
        fclose(dstFile);
        return true;
    }
  
    return false;
}

char* concatPaths(const char* root, const char* toAppend)
{
    //if (root == "" || root[0] == '\0') {
    //    // If root is empty, simply return a copy of 'toAppend'
    //    return _strdup(toAppend);
    //}
    
    // check if root path ends with \ or / and save it into a variable:
    bool isRequiredTrailingSlash = root[strlen(root) - 1] != '/' &&
                                   root[strlen(root) - 1] != '\\';

    // calculate length of the concatinated path:
    // hint: output length = strlen + strlen [sometimes, + 1]
    size_t concatPathLength = strlen(root) + strlen(toAppend) + isRequiredTrailingSlash;
    if (concatPathLength == 0)
        return NULL;

    char* concatPath = (char*) malloc(concatPathLength + 1);
    if (!concatPath)
        return NULL;

    // use strcpy and strcat to construct the output:
    strcpy(concatPath, root);
    if (isRequiredTrailingSlash) strcat(concatPath, "/");
    strcat(concatPath, toAppend);

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
