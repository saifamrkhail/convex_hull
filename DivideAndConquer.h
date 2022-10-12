//
// Created by saif on 10/11/22.
//

#ifndef CONVEX_HULL_DIVIDEANDCONQUER_H
#define CONVEX_HULL_DIVIDEANDCONQUER_H

#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <set>

using namespace cv;
using namespace std;

struct comparePoint {
    bool operator()(const Point & a, const Point & b) {
        if (a.x < b.x) return true;
        if (a.x > b.x) return false;
        if (a.y < b.y) return true;
        return false;
    }
};

class DivideAndConquer {

public:
    //storing the center point of polygon
    Point mid;

    //calculating the quadrant of a particular point
    int quad(Point p);

    //if line is touching the polygon
    int calcLine(Point a, Point b, Point c);

    //comparing functions for sorting
    bool compare(Point p1, Point q1);

    //finding the upper tangent for both polygons
    vector<Point> merger(vector<Point> a, vector<Point> b);

    //brute force algo to find convex hull
    vector<Point> bruteHull(vector<Point> a);

    //returning the value of convex hull
    vector<Point> convexHull(vector<Point> points);

    //draw convex hull step by step
    void convexHullVis(vector<cv::Point> points, vector<cv::Point>& hull, cv::Mat& matrix);
};

#endif //CONVEX_HULL_DIVIDEANDCONQUER_H
