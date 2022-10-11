//
// Created by saif on 10/11/22.
//

#ifndef CONVEX_HULL_DIVIDE_CONQUER_H
#define CONVEX_HULL_DIVIDE_CONQUER_H

#include <algorithm>
#include <utility>
#include <vector>
#include <set>

using namespace std;

class divide_conquer {

public:
    //storing the center point of polygon
    pair<int, int> mid;

    //calculating the quadrant of a particular point
    int quad(pair<int, int> p);

    //if line is touching the polygon
    int calc_line(pair<int, int> a, pair<int, int> b, pair<int, int> c);

    //comparing functions for sorting
    bool compare(pair<int, int> p1, pair<int, int> q1);

    //finding the upper tangent for both polygons
    vector<pair<int, int>> merger(vector<pair<int, int> > a, vector<pair<int, int> > b);

    //brute force algo to find convex hull
    vector<pair<int, int>> bruteHull(vector<pair<int, int>> a);

    //returning the value of convex hull
    vector<pair<int, int>> divide(vector<pair<int, int>> a);
};

#endif //CONVEX_HULL_DIVIDE_CONQUER_H
