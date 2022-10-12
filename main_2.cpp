#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <algorithm>
#include <iostream> 
#include <fstream> 
#include <string>
#include <sstream>
#include <vector>

#include "DivideAndConquer.h"
#include "Giftwrapping.cpp"
#include "Timing.h"

using namespace cv;
using namespace std;

int g_switch_value = 0;
int g_switch_value_performance = 0;
int g_switch_value_random_or_file = 0;

void pointsFromFile(std::vector<cv::Point2f>& points, std::string fname) {
    std::ifstream infile(fname);
    std::string line;
    std::string x, y;
    while (std::getline(infile, line)) {
        std::stringstream ls(line);
        std::getline(ls, x, ',');
        std::getline(ls, y);
        cv::Point2f p(std::stof(x), std::stof(y));
        points.push_back(p);
    }
    infile.close();
}

static void help(char **argv) {
    cout << "\nThis program demonstrates the use of different convexHull algorithms.\n"
         << "Call:\n"
         << argv[0] << endl;
}

void performanceTest(int cols, int rows) {
    Timing *measureTime = Timing::getInstance();
    vector<Point2f> points;
    RNG &rng_perf = theRNG();
    char prnt;

    if (g_switch_value_random_or_file == 0) {
        // random points
        // number of points
        int i, count = 1000;
        for (i = 0; i < count; i++) {
            Point2f pt;
            pt.x = (float)rng_perf.uniform(cols / 4, cols * 3 / 4);
            pt.y = (float)rng_perf.uniform(rows / 4, rows * 3 / 4);
            points.push_back(pt);
        }
    } else {
        // points from file
        cout << "Enter filename:" << endl;
        string fname;
        cin >> fname;
        cout << "Print Hull Points [Y/N]:" << endl;
 
        cin >> prnt;
        pointsFromFile(points, fname);
    }

    vector<Point2f> hull;
    if (g_switch_value == 0) {
        // OpenCV
        // measureTime->startSetup();
        cout << "\nOpenOV convexHull algorithm" << endl;
        measureTime->startRecord("Performance Test - Open CV");
        // measureTime->startComputation();
        convexHull(points, hull, true);
        // g_switch_value_performance = 0;
        measureTime->stopRecord("Performance Test - Open CV");
        measureTime->print(true);
        // cout << "\nTime:" << measureTime->getResults() << endl;
    }
    else if (g_switch_value == 1) {
        // Giftwrapping
        cout << "\nGiftwrapping convexHull algorithm" << endl;
        measureTime->startRecord("Performance Test - Giftwrapping");
        // measureTime->startComputation();
        Giftwrapping::convexHull(points, hull);
        // g_switch_value_performance = 0;
        measureTime->stopRecord("Performance Test - Giftwrapping");
        measureTime->print(true);
    }
    else {

    }
    cout << "Points: " << to_string(points.size()) << endl;

    if (g_switch_value_random_or_file == 1) {
        if (prnt == 'Y' || prnt == 'y') {
            for (Point2f p : hull) {
                cout << "(" << p.x << ", " << p.y << ")" << endl;
            }
        }
    }
}

void switch_callback(int, void *) {
    if (g_switch_value == 0) {
        cout << "\nOpenCV" << endl;
    } else if (g_switch_value == 1) {
        cout << "\nGiftwrapping" << endl;
    } else {
        cout << "\nDivide & Conquer" << endl;
    }
}

void switch_callback_perf(int, void *) {
    if (g_switch_value_performance == 0) {
        cout << "\nVisual" << endl;
    } else {
        cout << "\nPerformance" << endl;
    }
}

void switch_callback_rnd_file(int, void*) {
    if (g_switch_value_random_or_file == 0) {
        cout << "\nRandom points" << endl;
    }
    else {
        cout << "\nFile" << endl;
    }
}

int main(int argc, char *argv[]) {

    std::cout << "Divide and Conquer Algorithm" << std::endl;
    DivideAndConquer divideAndConquer;

    CommandLineParser parser(argc, argv, "{help h||}");
    if (parser.has("help")) {
        help(argv);
        return 0;
    }
    Mat img(500, 500, CV_8UC3);

    // Name the main window
    namedWindow("Convex Hull", 1);

    createTrackbar(
            "CV G D&C",
            "Convex Hull",
            &g_switch_value,
            2,
            switch_callback
    );

    createTrackbar(
            "Rnd File",
            "Convex Hull",
            &g_switch_value_random_or_file,
            1,
            switch_callback_rnd_file
    );

    createTrackbar(
        "Vis Perf",
        "Convex Hull",
        &g_switch_value_performance,
        1,
        switch_callback_perf
    );

    RNG &rng = theRNG();
    while (true) {
        if (g_switch_value_performance == 0) {
            // visualisation


            // random points beween (count: 10 and 15)
            int i, count = (unsigned) rng % 5 + 10;

            vector<Point2f> points;

            for (i = 0; i < count; i++) {
                Point2f pt;
                pt.x = (float)rng.uniform(img.cols / 4, img.cols * 3 / 4);
                pt.y = (float)rng.uniform(img.rows / 4, img.rows * 3 / 4);
                points.push_back(pt);
            }

            Mat whiteMatrix(500, 500, CV_8UC3, Scalar(255, 255, 255));

            for (i = 0; i < count; i++) {
                // Point center;
                // center.x = (int)points[i].x;
                // center.y = (int)points[i].y;
                // circle(whiteMatrix, center, 3, Scalar(0, 0, 255), FILLED, LINE_AA);
                circle(whiteMatrix, points[i], 3, Scalar(0, 0, 255), FILLED, LINE_AA);
            }

            // imshow("Convex Hull", whiteMatrix);

            vector<Point2f> hull;

            if (g_switch_value == 0) {
            // OpenCV convexHull algorithm
                // Calculate hull points
                convexHull(points, hull, true);
                // clear canvas (white color)
                whiteMatrix = Scalar::all(255);

                // polylines works with integer coordinates only!
                vector<Point> hull_integer;
                for (int j = 0; j < hull.size(); j++) {
                    hull_integer.push_back((Point)hull[j]);
                }
                for (i = 0; i < count; i++) {
                    circle(whiteMatrix, points[i], 3, Scalar(0, 0, 255), FILLED, LINE_AA);
                }
                // polylines(whiteMatrix, hull, true, Scalar(0, 255, 0), 1, LINE_AA);
                polylines(whiteMatrix, hull_integer, true, Scalar(0, 255, 0), 1, LINE_AA);
                imshow("Convex Hull", whiteMatrix);
            }
            else if (g_switch_value == 1)
            {
                // Giftwrapping algorithm
                // generateRandPoints(points, 20, 500, 500);
                // cv::Mat whiteMatrix(500, 500, CV_8UC3, cv::Scalar(255, 255, 255));
                // Scalar point_color(0, 0, 0);
                // cv::namedWindow("Convex Hull");
                /*
                for (Point p : points) {
                    line(whiteMatrix, p, p, point_color, 10);
                }
                */

                // clear canvas
                whiteMatrix = Scalar::all(255);

                // draw points
                for (i = 0; i < count; i++) {
                    circle(whiteMatrix, points[i], 3, Scalar(0, 0, 255), FILLED, LINE_AA);
                }

                Giftwrapping::convexHullVis(points, hull, whiteMatrix);
                // imshow("Convex Hull", whiteMatrix);

                // break;
            }
            else {
                // Divide and Conquer

            }

            // divide and conquer step by step
            // divideAndConquer.convexHullVis(points, hull, whiteMatrix);

            // convex hull in one shot
            /*hull = divideAndConquer.convexHull(points);
            img = Scalar::all(0);
            for (i = 0; i < count; i++) {
                circle(img, points[i], 3, Scalar(0, 0, 255), FILLED, LINE_AA);
            }
            polylines(img, hull, true, Scalar(0, 255, 0), 1, LINE_AA);
            imshow("Convex Hull", img);*/

            //convexHull of opencv lib
            /*convexHull(points, hull, true);
            img = Scalar::all(0);
            for (i = 0; i < count; i++) {
                circle(img, points[i], 3, Scalar(0, 0, 255), FILLED, LINE_AA);
            }
            polylines(img, hull, true, Scalar(0, 255, 0), 1, LINE_AA);
            imshow("Convex Hull", img);*/

        } else {
            // performance
            performanceTest(img.cols, img.rows);
            setTrackbarPos("Vis Perf", "Convex Hull", 0);
        }
        char key = (char) waitKey();

        if (key == 27 || key == 'q' || key == 'Q') {
            break;
        }

    }

    return 0;
}
