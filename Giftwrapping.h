#include <vector>
#include <iostream>
#include <opencv2/core/types.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <chrono>
#include "Timing.h"
#pragma once

class Giftwrapping {
public:
	static void convexHull(std::vector<cv::Point2f> points, std::vector<cv::Point2f>& hull);
	static void convexHullVis(std::vector<cv::Point2f> points, std::vector<cv::Point2f>& hull, cv::Mat& matrix);
	static float orient2d(cv::Point2f a, cv::Point2f b, cv::Point2f c);
};
