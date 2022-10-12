#include "Giftwrapping.h"

void Giftwrapping::convexHull(std::vector<cv::Point2f> points, std::vector<cv::Point2f>& hull)
{
	int num_points = points.size();
	if (num_points < 3) return;
	float x_min = points[0].x;
	int i_min = 0;
	for (int i = 0; i < num_points; i++) {
		if (points[i].x < x_min) {
			i_min = i;
		}
	}
	int p = i_min, q;
	do {
		hull.push_back(points[p]);
		q = (p + 1) % num_points;
		for (int i = 0; i < num_points; i++) {
			if (orient2d(points[p], points[q], points[i]) < 0) {
				q = i;
			}
		}
		p = q;
	} while (p != i_min);
}


float Giftwrapping::orient2d(cv::Point2f a, cv::Point2f b, cv::Point2f c)
{
	return (a.x - c.x) * (b.y - c.y) - (b.x - c.x) * (a.y - c.y);
}
