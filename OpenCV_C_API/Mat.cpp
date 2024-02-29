#include "Mat.h"
#include "opencv_linker.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "overlay.h"
using namespace cv;

CvMAT MAT_Create(int rows, int cols)
{
	return (CvMAT) new Mat(rows, cols, CV_8UC3);
}

void MAT_Free(CvMAT mat)
{
	Mat* m = (Mat*)mat;
	delete m;
}

CvMAT MAT_Clone(const CvMAT mat)
{
	Mat* m = (Mat*)mat;
	Mat * copy = new Mat(m->clone());
	return (CvMAT)copy;
}

void MAT_SetColor(CvMAT mat, uint8_t color[])
{
	Mat* m = (Mat*)mat;
	Scalar c;
	switch (m->channels()) {
	case 1: c = Scalar(color[0]); break;
	case 2: c = Scalar(color[0], color[1]); break;
		// RGB->BGR
	case 3: c = Scalar(color[2], color[1], color[0]); break;
	case 4: c = Scalar(color[2], color[1], color[0], color[3]); break;
	default:
		return;
	};
	*m = c;
}
int MAT_IsEqual(CvMAT a, CvMAT b)
{
	Mat* m_a = (Mat *)a;
	Mat* m_b = (Mat *)b;
	if (m_a->size() != m_b->size() ||
		m_a->type() != m_b->type() ||
		m_a->channels() != m_b->channels())
		return false;

	Vec4f diff = cv::sum(*m_a != *m_b);
	for (int i = 0; i < diff.channels; i++)
		if (diff[i] != 0)
			return false;
	
	return true;
}

CvMAT MAT_Read(const char* filePath)
{
	Mat * m = new Mat(imread(filePath, -1));
	return (void*)m;
}

void MAT_Write(const char* filePath, CvMAT mat)
{
	Mat* m = (Mat*)mat;
	imwrite(filePath, *m);
}

void MAT_CopyTo(CvMAT srcMat, CvMAT dstMat, int TL[2])
{
	Mat* src = (Mat*)srcMat;
	Mat* dst = (Mat*)dstMat;
	Rect dst_roi(TL[0], TL[1], src->cols, src->rows);
	Rect dst_bounds(0, 0, dst->cols, dst->rows);
	Rect dst_adjusted_roi = dst_roi & dst_bounds;
	if (false == dst_adjusted_roi.empty())
	{
		Rect src_adjustedRoi(0, 0, dst_adjusted_roi.width, dst_adjusted_roi.height);
		(*src)(src_adjustedRoi).copyTo((*dst)(dst_adjusted_roi));
	}
}

void MAT_CopyTo_WithTransparency(CvMAT srcMat, CvMAT dstMat, int TL[2])
{
	Mat* src = (Mat*)srcMat;
	Mat* dst = (Mat*)dstMat;
	Rect dst_roi(TL[0], TL[1], src->cols, src->rows);
	Rect dst_bounds(0, 0, dst->cols, dst->rows);
	Rect dst_adjusted_roi = dst_roi & dst_bounds;
	if (false == dst_adjusted_roi.empty())
	{
		Rect src_adjustedRoi(0, 0, dst_adjusted_roi.width, dst_adjusted_roi.height);
		Mat src_roi = (*src)(src_adjustedRoi);
		std::vector<Mat> channels;
		split(src_roi, channels);
		Mat & transparency = channels.back();
		src_roi.copyTo((*dst)(dst_adjusted_roi), transparency);
	}
}

size_t MAT_Width(CvMAT m) { return ((Mat*)m)->cols; }
size_t MAT_Height(CvMAT m) { return ((Mat*)m)->rows; }

void Cv_ImShow(const char* windowName, CvMAT mat)
{
	Mat* m = (Mat*)mat;
	imshow(windowName, *m);
}

int Cv_WaitKey(int delay)
{
	return cv::waitKey(delay);
}

void Cv_PutText(CvMAT mat, const char * text,
	int origin_x, int origin_y, 
	float fontScale, int thickness)
{
	Mat* m = (Mat*)mat;
	cv::putText(*m, text, Point(origin_x, origin_y), 
		/*fotFace*/cv::FONT_HERSHEY_DUPLEX,
		fontScale,
		/*color*/Scalar(0,200,255), thickness);
}

void Cv_DestroyAllWindows()
{
	cv::destroyAllWindows();
}

