#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <algorithm>

#include "DivideAndConquer.h"
#include "Timing.h"

using namespace cv;
using namespace std;

int g_switch_value = 0;
int g_switch_value_performance = 0;

static void help(char **argv) {
    cout << "\nThis program demonstrates the use of different convexHull algorithms.\n"
         << "Call:\n"
         << argv[0] << endl;
}


void performanceTest(int cols, int rows) {
    Timing *measureTime = Timing::getInstance();
    vector<Point> points;
    RNG &rng_perf = theRNG();
    // number of points
    int i, count = 1000000;
    for (i = 0; i < count; i++) {
        Point pt;
        pt.x = rng_perf.uniform(cols / 4, cols * 3 / 4);
        pt.y = rng_perf.uniform(rows / 4, rows * 3 / 4);
        points.push_back(pt);
    }
    vector<Point> hull;
    if (g_switch_value == 0) {
        // OpenCV
        // measureTime->startSetup();
        cout << "\nOpenOV convexHull algorithm" << endl;
        measureTime->startRecord("Open CV");
        // measureTime->startComputation();
        convexHull(points, hull, true);
        // g_switch_value_performance = 0;
        measureTime->stopRecord("Open CV");
        measureTime->print(true);
        // cout << "\nTime:" << measureTime->getResults() << endl;
    }
}

void switch_callback(int, void *) {
    if (g_switch_value == 0) {
        cout << "\nOpenCV" << endl;
    } else if (g_switch_value == 1) {
        cout << "\nGraham Scan" << endl;
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


int main(int argc, char *argv[]) {
    std::cout << "Divide and Conquer Algorithm" << std::endl;
    DivideAndConquer div_conq;

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
            "Vis Perf",
            "Convex Hull",
            &g_switch_value_performance,
            1,
            switch_callback_perf
    );

    RNG &rng = theRNG();
    while (true) {
        if (g_switch_value_performance == 0)
            // visualisation
        {
            int i, count = (unsigned) rng % 30 + 20;
            vector<Point> points;
            for (i = 0; i < count; i++) {
                Point pt;
                pt.x = rng.uniform(img.cols / 4, img.cols * 3 / 4);
                pt.y = rng.uniform(img.rows / 4, img.rows * 3 / 4);
                points.push_back(pt);
            }

            //TODO show here given Points

            sort(points.begin(), points.end(), [](Point p, Point q) {
                if (p.x < q.x) return true;
                if (p.x > q.x) return false;
                if (p.y < q.y) return true;
                return false;
            });

            vector<Point> hull = div_conq.convexHull(points);
            //convexHull(points, hull, true);

            img = Scalar::all(0);
            for (i = 0; i < count; i++) {
                circle(img, points[i], 3, Scalar(0, 0, 255), FILLED, LINE_AA);
            }

            polylines(img, hull, true, Scalar(0, 255, 0), 1, LINE_AA);
            imshow("Convex Hull", img);

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
