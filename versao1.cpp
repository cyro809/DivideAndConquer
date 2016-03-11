#include <iostream>
#include <algorithm>
#include <fstream>
#include <utility>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

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

bool comparePoints (const Point &p1, const Point &p2)
{
    if( p1.x < p2.x)
        return 1;
    else if(p1.x == p2.x){
        return (p1.y < p2.y);
    }
    return 0;
}

float isLeft (const Point &P0, const Point &P1, const Point &P2)
{
    return (P1.x - P0.x)*(P2.y - P0.y) - (P2.x - P0.x)*(P1.y - P0.y);
}

vector<Point> convexHull(vector<Point> &P)
{
    int n = P.size(), k = 0;
	vector<Point> H(2*n);

	// Sort points lexicographically
	sort(P.begin(), P.end(), comparePoints);

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

vector<Point> mergeHull(vector<Point> &ha, vector<Point> &hb)
{
    std::vector<Point> hull;
    hull.reserve( ha.size() + hb.size()); // preallocate memory

    hull.insert( hull.end(), ha.begin(), ha.end() );
    hull.insert( hull.end(), hb.begin(), hb.end() );

    std::vector<Point> merged_hull = convexHull(hull);
    merged_hull.pop_back();
    return merged_hull;
}


vector<Point> divideAndConquer(vector<Point> &points)
{
    vector<Point> HA;
    vector<Point> HB;
    vector<Point> S;

    if(points.size() > 3)
    {
        int max_x = points[points.size()-1].x;
        int min_x = points[0].x;
        int splitter = (max_x + min_x)/2;

        for(int i=0;i<points.size();i++)
        {
            if(points[i].x <= splitter)
            {
                HA.push_back(points[i]);
            }
            else
            {
                HB.push_back(points[i]);
            }
        }
        if(HA.size() == points.size() || HB.size() == points.size()) return points;

        HA = divideAndConquer(HA);
        HB = divideAndConquer(HB);
        S = mergeHull(HA,HB);
        return S;
    }
    else
    {
        return points;
    }
}

int main()
{
    /* TESTE PARA DIVIDE AND CONQUER */

    ifstream inData("input.txt");
    int x,y;
    char delim;
    vector<Point> S, initialS;
    for(int i=0;i<30;i++)
    {
        inData>>x>>delim>>y;
        S.push_back(Point(x,y));
    }

    std::sort(S.begin(),S.end(), comparePoints);
    initialS = S;

    S = divideAndConquer(S);
    for(int i=0;i<S.size();i++) S[i].print();

    ALLEGRO_DISPLAY *display = NULL;
    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    al_init_primitives_addon();

    display = al_create_display(200,200);
    al_clear_to_color(al_map_rgb(255,255,255));
    int offset = 50, i;

    for(i=0;i<initialS.size();i++) {
        al_draw_filled_circle(initialS[i].x + offset, initialS[i].y + offset, 3, al_map_rgb(0,0,0));
    }

    for (i = 0; i < S.size() - 1; i++) {
        al_draw_line(S[i].x + offset, S[i].y + offset,
            S[i+1].x + offset, S[i+1].y + offset, al_map_rgb(255,0,0), 2);
    }
    al_draw_line(S[i].x + offset, S[i].y + offset,
        S[0].x + offset, S[0].y + offset, al_map_rgb(255,0,0), 2);


    al_flip_display();
    al_rest(30.0);
    al_shutdown_primitives_addon();
    al_destroy_display(display);

    return 0;
}
