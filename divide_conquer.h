//
// Created by saif on 10/11/22.
//

#ifndef CONVEX_HULL_DIVIDE_CONQUER_H
#define CONVEX_HULL_DIVIDE_CONQUER_H

#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>
#include <utility>
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

class divide_conquer {

public:
    //storing the center point of polygon
    Point mid;

    //calculating the quadrant of a particular point
    int quad(Point p);

    //if line is touching the polygon
    int calc_line(Point a, Point b, Point c);

    //comparing functions for sorting
    bool compare(Point p1, Point q1);

    //finding the upper tangent for both polygons
    vector<Point> merger(vector<Point> a, vector<Point> b);

    //brute force algo to find convex hull
    vector<Point> bruteHull(vector<Point> a);

    //returning the value of convex hull
    vector<Point> divide(vector<Point> a);
};

#endif //CONVEX_HULL_DIVIDE_CONQUER_H
