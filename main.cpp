#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

#define above(P,Vi,Vj)  (isLeft(P,Vi,Vj) > 0)
#define below(P,Vi,Vj)  (isLeft(P,Vi,Vj) < 0)

using namespace std;

class Point
{
    public:
        Point(double px, double py){ x = px; y = py; }
        Point() {x = 0; y = 0; }
        void print(){ cout<<"("<<x<<","<<y<<")"<<endl; }
        double x;
        double y;

};

float isLeft (Point P0, Point P1, Point P2)
{
    return (P1.x - P0.x)*(P2.y - P0.y) - (P2.x - P0.x)*(P1.y - P0.y);
}

vector<Point> divideAndConquer(vector<Point> points)
{
    int lower_tangent_points[2];
    if(points.size() > 3)
    {
        int ha_length = points.size()/2;
        Point ha[ha_length];

        Point *hb;
        int hb_length = points.size()/2;

        Point *convex_hull;

        if(points.size()%2 == 0)
        {
            hb = new Point[hb_length];
        }
        else
        {
            hb_length++;
            hb = new Point[hb_length];
        }


        int b = 0;
        for(int i=0;i<points.size();i++)
        {
            if(i < points.size()/2)
            {
                ha[i] = points[i];
                ha[i].print();
            }
            else
            {
                hb[b] = points[i];
                hb[b].print();
                b++;
            }
        }
        cout<<endl;
        divideAndConquer(ha,ha_length);

        cout<<endl;
        divideAndConquer(hb,hb_length);
        /* Merge Hull HA and HB,
           compute Upper and Lower Tangents
           discard all points between these to tangents */
    }
    else
    {
        // return points;
    }



}

vector<Point> mergeHull(vector<Point> ha, vector<Point> hb)
{
    vector<Point> hull;
    vector<Point> merged_hull;
    hull.reserve( ha.size() + hb.size()); // preallocate memory
    hull.insert( hull.end(), ha.begin(), ha.end() );
    hull.insert( hull.end(), hb.begin(), hb.end() );
    merged_hull = convex_hull(hull);

    return merged_hull;
}

vector<Point> convex_hull(vector<Point> P)
{
	int n = P.size(), k = 0;
	vector<Point> H(2*n);

	// Sort points lexicographically
	//sort(P.begin(), P.end());

	// Build lower hull
	for (int i = 0; i < n; ++i) {
		while (k >= 2 && isLeft(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	// Build upper hull
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && isLeft(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	H.resize(k);
	return H;
}

int main()
{
    std::vector<Point> ha = {Point(1,1), Point(2,2), Point(3,3), Point(4,3), Point(4,2)};
    std::vector<Point> hb = {Point(5,1), Point(6,3), Point(7,4), Point(7,5), Point(8,2)};
    std::vector<Point> h;

    h.reserve( ha.size() + hb.size()); // preallocate memory
    h.insert( h.end(), ha.begin(), ha.end() );
    h.insert( h.end(), hb.begin(), hb.end() );
    std::vector<Point> convex = convex_hull(h);

    for(int i=0; i<convex.size();i++)
    {
        convex[i].print();
    }
    return 0;
}
