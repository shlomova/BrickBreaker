#pragma once

#ifdef OPENCV_API_EXPORT
	#define OPENCV_API __declspec(dllexport)
#else
	#define OPENCV_API __declspec(dllimport)
#endif
