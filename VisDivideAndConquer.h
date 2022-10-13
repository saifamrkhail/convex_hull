//
// Created by saif on 10/13/22.
//

#ifndef CONVEX_HULL_VISDIVIDEANDCONQUER_H
#define CONVEX_HULL_VISDIVIDEANDCONQUER_H

#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <set>

using namespace cv;
using namespace std;

struct VisComparePoint {
    bool operator()(const Point2f & a, const Point2f & b) const {
        if (a.x < b.x) return true;
        if (a.x > b.x) return false;
        if (a.y < b.y) return true;
        return false;
    }
};

class VisDivideAndConquer {
public:
    //storing the center point of polygon
    Point2f mid;

    //calculating the quadrant of a particular point
    int quad(Point2f p);

    //if line is touching the polygon
    int calcLine(Point2f a, Point2f b, Point2f c);

    //comparing functions for sorting
    bool compare(Point2f p1, Point2f q1);

    //finding the upper tangent for both polygons
    vector<Point2f> merger(vector<Point2f> a, vector<Point2f> b);

    //brute force algo to find convex hull
    vector<Point2f> bruteHull(vector<Point2f> a);

    //returning the value of convex hull
    vector<Point2f> visConvexHull(vector<Point2f> points);

};


#endif //CONVEX_HULL_VISDIVIDEANDCONQUER_H
