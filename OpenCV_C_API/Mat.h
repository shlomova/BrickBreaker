#pragma once
#include <stdint.h>
#include "ExportDefs.h"
#define CvMAT void *

#ifdef __cplusplus
extern "C" {
#endif

	/**
	@param rows Number of rows in a 2D array.
	@param cols Number of columns in a 2D array.
	The returned image should be freed afterwards with MAT_Free()
	*/
	OPENCV_API CvMAT MAT_Create(int rows, int cols);
	OPENCV_API void MAT_Free(CvMAT mat);
	
	OPENCV_API CvMAT MAT_Clone(const CvMAT mat);

	/*
	@param mat - all of whose pixels will be set to color
	@param color - 1d array of dimension at least as mat channels, with color values.
	*/
	OPENCV_API void MAT_SetColor(CvMAT mat, uint8_t color[]);

	/*
	* Checks if two images are identical. 
	* Returns 0 if false, or non zero value if true.
	*/
	OPENCV_API int MAT_IsEqual(CvMAT a, CvMAT b);

	/*
	The returned image should be freed afterwards with MAT_Free()
	*/
	OPENCV_API CvMAT MAT_Read(const char* filePath);

	OPENCV_API void MAT_Write(const char* filePath, CvMAT mat);

	/*
	@param ROI = x0,y0,W,H
	*/
	OPENCV_API void MAT_CopyTo(CvMAT srcMat, CvMAT dstMat, int TL[2]);

	/*
	@param TL = Top Left point in destination image.
	Same as CopyTo, but takes in account the transparency.
	*/
	OPENCV_API void MAT_CopyTo_WithTransparency(CvMAT srcMat, CvMAT dstMat, int TL[2]);

	OPENCV_API size_t MAT_Width(CvMAT m);
	OPENCV_API size_t MAT_Height(CvMAT m);

	/*
	@param windowName - the title of the window to be created (and it's unique identifier)
	@param mat - image to show
	*/
	OPENCV_API void Cv_ImShow(const char* windowName, CvMAT mat);

	/*
	Waits for a key to be hit and returns the key code.
	Must be called after Cv_ImShow in order to let the window thread to start.
	@param	delay_ms - in milliseconds.
			if delay = 0, waits for unlimited time to a key hit.
	*/
	OPENCV_API int Cv_WaitKey(int delay_ms);
	
	OPENCV_API void Cv_PutText(CvMAT mat, const char* text,
		int origin_x, int origin_y,
		float fontScale, int thickness);

	/*
	* Closes all windows that were opened with Cv_ImShow
	*/
	OPENCV_API void Cv_DestroyAllWindows();


#ifdef __cplusplus
}
#endif