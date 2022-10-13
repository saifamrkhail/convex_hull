//
// Created by saif on 10/13/22.
//

#include "VisDivideAndConquer.h"

cv::Mat whiteMatrix(500, 500, CV_8UC3, cv::Scalar(255, 255, 255));
cv::Scalar green(0, 255, 0);
cv::Scalar red(0, 0, 255);
cv::Scalar black(0, 0, 0);
char key;
bool firstRun = true;

//calculating the quadrant of a particular Point2f
int VisDivideAndConquer::quad(Point2f p) {
    if (p.x >= 0 && p.y >= 0)
        return 1;
    if (p.x <= 0 && p.y >= 0)
        return 2;
    if (p.x <= 0 && p.y <= 0)
        return 3;
    return 4;
}

//if line is touching the polygon
int VisDivideAndConquer::calcLine(Point2f a, Point2f b, Point2f c) {

    return (b.y-a.y)*(c.x-b.x) - (c.y-b.y)*(b.x-a.x);
}

//comparing functions for sorting
bool VisDivideAndConquer::compare(Point2f p1, Point2f q1) {
    Point2f p = Point2f(p1.x - mid.x,p1.y - mid.y);
    Point2f q = Point2f(q1.x - mid.x,q1.y - mid.y);
    int one = quad(p);
    int two = quad(q);
    if (one != two)
        return (one < two);
    return (p.y * q.x < q.y * p.x);
}

//finding the upper tangent for both polygons
vector<Point2f> VisDivideAndConquer::merger(vector<Point2f> a, vector<Point2f> b) {

    int n1 = a.size(), n2 = b.size();

    if (n1 == 0) {
        return b;
    }

    if (n2 == 0) {
        return a;
    }

    int ia = 0, ib = 0;

    //calculating rightmost point of a
    for (int i = 1; i < n1; i++) {
        if (a[i].x > a[ia].x) {
            ia = i;
        }
    }

    cv::line(whiteMatrix, a[ia], a[ia], red, 10);
    cv::imshow("Convex Hull", whiteMatrix);
    key = cv::waitKey(0);
    if (key == 27 || key == 'q' || key == 'Q') {
        exit(0);
    }

    //calculating leftmost point of b
    for (int i = 1; i < n2; i++) {
        if (b[i].x < b[ib].x) {
            ib = i;
        }
    }

    cv::line(whiteMatrix, b[ib], b[ib], green, 10);
    cv::imshow("Convex Hull", whiteMatrix);
    key = cv::waitKey(0);
    if (key == 27 || key == 'q' || key == 'Q') {
        exit(0);
    }

    int inda = ia, indb = ib;
    bool done = 0;
    //calculating the upper tangent
    while (!done) {
        done = 1;

        while (calcLine(b[indb], a[inda], a[(inda + 1) % n1]) > 0) {
            inda = (inda + 1) % n1;
        }

        cv::line(whiteMatrix, a[inda], a[inda], green, 10);
        cv::imshow("Convex Hull", whiteMatrix);
        key = cv::waitKey(0);
        if (key == 27 || key == 'q' || key == 'Q') {
            exit(0);
        }

        while (calcLine(a[inda], b[indb], b[(n2 + indb - 1) % n2]) <= 0) {
            indb = (n2 + indb - 1) % n2;
            done = 0;
        }

        cv::line(whiteMatrix, b[indb], b[indb], green, 10);
        cv::imshow("Convex Hull", whiteMatrix);
        key = cv::waitKey(0);
        if (key == 27 || key == 'q' || key == 'Q') {
            exit(0);
        }
    }

    int uppera = inda, upperb = indb;
    inda = ia, indb = ib;
    done = 0;

    //calculating the lower tangent
    while (!done) {
        done = 1;
        while (calcLine(a[inda], b[indb], b[(indb + 1) % n2]) >= 0)
            indb = (indb + 1) % n2;
        while (calcLine(b[indb], a[inda], a[(n1 + inda - 1) % n1]) <= 0) {
            inda = (n1 + inda - 1) % n1;
            done = 0;
        }
    }

    int lowera = inda, lowerb = indb;
    vector<Point2f> ret;
    //merging the two polygons to get convex hull
    int ind = uppera;
    ret.push_back(a[uppera]);

    cv::line(whiteMatrix, a[uppera], b[upperb], green, 10);
    cv::imshow("Convex Hull", whiteMatrix);
    key = cv::waitKey(0);
    if (key == 27 || key == 'q' || key == 'Q') {
        exit(0);
    }


    while (ind != lowera) {
        ind = (ind + 1) % n1;
        ret.push_back(a[ind]);

        cv::line(whiteMatrix, a[ind], a[ind], green, 10);
        cv::imshow("Convex Hull", whiteMatrix);
        key = cv::waitKey(0);
        if (key == 27 || key == 'q' || key == 'Q') {
            exit(0);
        }
    }

    ind = lowerb;
    ret.push_back(b[lowerb]);

    cv::line(whiteMatrix, a[lowera], b[lowerb], green, 10);
    cv::imshow("Convex Hull", whiteMatrix);
    key = cv::waitKey(0);
    if (key == 27 || key == 'q' || key == 'Q') {
        exit(0);
    }

    while (ind != upperb) {
        ind = (ind + 1) % n2;
        ret.push_back(b[ind]);
    }

    return ret;
}

//brute force algo to find convex hull
vector<Point2f> VisDivideAndConquer::bruteHull(vector<Point2f> a) {

    set<Point2f,VisComparePoint> s;

    for (int i = 0; i < a.size(); i++) {
        for (int j = i + 1; j < a.size(); j++) {
            int x1 = a[i].x, x2 = a[j].x;
            int y1 = a[i].y, y2 = a[j].y;
            int a1 = y1 - y2;
            int b1 = x2 - x1;
            int c1 = x1 * y2 - y1 * x2;
            int pos = 0, neg = 0;
            for (int k = 0; k < a.size(); k++) {
                if (a1 * a[k].x + b1 * a[k].y + c1 <= 0)
                    neg++;
                if (a1 * a[k].x + b1 * a[k].y + c1 >= 0)
                    pos++;
            }
            if (pos == a.size() || neg == a.size()) {
                s.insert(a[i]);
                s.insert(a[j]);

                cv::line(whiteMatrix, a[i], a[j], red, 10);
                cv::imshow("Convex Hull", whiteMatrix);
                key = cv::waitKey(0);
                if (key == 27 || key == 'q' || key == 'Q') {
                    exit(0);
                }
            }

        }
    }

    vector<Point2f> ret;
    for (auto e: s) {
        ret.push_back(e);
    }

    //moving through anti clockwise direction
    mid = {0, 0};
    int n = ret.size();
    for (int i = 0; i < n; i++) {
        mid.x += ret[i].x;
        mid.y += ret[i].y;
        ret[i].x *= n;
        ret[i].y *= n;
    }

    sort(ret.begin(), ret.end(), [this] (Point2f p1, Point2f q1) {
        return compare(p1, q1);
    });

    for (int i = 0; i < n; i++) {
        ret[i] = Point2f(ret[i].x / n, ret[i].y / n);
    }

    return ret;
}

//returning the value of convex hull
vector<Point2f> VisDivideAndConquer::visConvexHull(vector<cv::Point2f> points) {

    if (firstRun) {
        firstRun = false;

        cv::namedWindow("Convex Hull");

        for (cv::Point p : points) {
            cv::line(whiteMatrix, p, p, black, 10);
        }

        cv::imshow("Convex Hull", whiteMatrix);
        key = cv::waitKey(0);

        if (key == 27 || key == 'q' || key == 'Q') {
            exit(0);
        }

        sort(points.begin(), points.end(), [](Point2f p, Point2f q) {
            if (p.x < q.x) return true;
            if (p.x > q.x) return false;
            if (p.y < q.y) return true;
            return false;
        });
    }

    if (points.size() <= 5) {
        return bruteHull(points);
    }

    // left contains the left half points
    // right contains the right half points
    vector<Point2f> left, right;

    for (int i = 0; i < points.size() / 2.0; i++) {
        left.push_back(points[i]);
    }

    for (int i = points.size() / 2.0; i < points.size(); i++) {
        right.push_back(points[i]);
    }

    //divide in left and right
    vector<Point2f> left_hull = visConvexHull(left);
    vector<Point2f> right_hull = visConvexHull(right);

    //merging the convex hulls
    vector<Point2f> hull = merger(left_hull, right_hull);

    return hull;
}