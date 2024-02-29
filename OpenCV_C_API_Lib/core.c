#include "core.h"
#include "Mat.h"

CvMat Mat_Create(int rows, int cols)
{
	return MAT_Create(rows, cols);
}

void Mat_Free(CvMat mat)
{
	MAT_Free(mat);
}

CvMat Mat_Clone(const CvMat mat)
{
	return MAT_Clone(mat);
}

void Mat_SetColor(CvMat mat, uint8_t color[])
{
	MAT_SetColor(mat, color);
}

int Mat_IsEqual(CvMat a, CvMat b)
{
	return MAT_IsEqual(a, b);
}
CvMat Mat_Read(const char* filePath)
{
	return MAT_Read(filePath);
}

void Mat_Write(const char* filePath, CvMat mat)
{
	MAT_Write(filePath, mat);
}

void Mat_CopyTo(CvMat srcMat, CvMat dstMat, int TL[2])
{
	MAT_CopyTo(srcMat, dstMat, TL);
}

void Mat_CopyTo_WithTransparency(CvMat srcMat, CvMat dstMat, int TL[2])
{
	MAT_CopyTo_WithTransparency(srcMat, dstMat, TL);
}

size_t Mat_Width(CvMat m)
{
	return MAT_Width(m);
}
size_t Mat_Height(CvMat m)
{
	return MAT_Height(m);
}

void CvImShow(const char* windowName, CvMat mat)
{
	Cv_ImShow(windowName, mat);
}

int CvWaitKey(int delay_ms)
{
	return Cv_WaitKey(delay_ms);
}

void CvPutText(CvMat mat, const char* text,
	int origin_x, int origin_y,
	float fontScale, int thickness)
{
	Cv_PutText(mat, text,
		origin_x, origin_y,
		fontScale,thickness);
}

void CvDestroyAllWindows()
{
	Cv_DestroyAllWindows();
}