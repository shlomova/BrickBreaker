#pragma once
#include <stdint.h>

#define CvMat void *

/**
@param rows Number of rows in a 2D array.
@param cols Number of columns in a 2D array.
The returned image should be freed afterwards with Mat_Free()
*/
CvMat Mat_Create(int rows, int cols);
void Mat_Free(CvMat mat);

CvMat Mat_Clone(const CvMat mat);

/*
@param mat - all of whose pixels will be set to color
@param color - 1d array of dimension at least as mat channels, with color values.
*/
void Mat_SetColor(CvMat mat, uint8_t color[]);

/*
The returned image should be freed afterwards with Mat_Free()
*/
int Mat_IsEqual(CvMat a, CvMat b);
CvMat Mat_Read(const char* filePath);

void Mat_Write(const char* filePath, CvMat mat);

/*
@param ROI = x0,y0,W,H
*/
void Mat_CopyTo(CvMat srcMat, CvMat dstMat, int TL[2]);

/*
@param TL = Top Left point in destination image.
Same as CopyTo, but takes in account the transparency.
*/
void Mat_CopyTo_WithTransparency(CvMat srcMat, CvMat dstMat, int TL[2]);

size_t Mat_Width(CvMat m);
size_t Mat_Height(CvMat m);

void CvPutText(CvMat mat, const char* text,
	int origin_x, int origin_y,
	float fontScale, int thickness);

/////////////// GUI related commands: /////////////
/*
@param windowName - the title of the window to be created (and it's unique identifier)
@param mat - image to show
*/
void CvImShow(const char* windowName, CvMat mat);

/*
Waits for a key to be hit and returns the key code.
Must be called after CvImShow in order to let the window thread to start.
@param	delay_ms - in milliseconds.
		if delay = 0, waits for unlimited time to a key hit.
*/
int CvWaitKey(int delay_ms);

/*
* Closes all windows that were opened with CvImShow
*/
void CvDestroyAllWindows();