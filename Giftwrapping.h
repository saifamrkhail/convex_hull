#include <vector>
#include <iostream>
#include <opencv2/core/types.hpp>
#pragma once

class Giftwrapping {
public:
	static void convexHull(std::vector<cv::Point2f> points, std::vector<cv::Point2f>& hull);
	static float orient2d(cv::Point2f a, cv::Point2f b, cv::Point2f c);
};