#include <iostream>

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

int *lowerTangent(Point *ha, Point* hb, int ha_length)
{
    int a = ha_length-1;
    int b = 0;
    bool done = false;

    while(!done)
    {
        done = true;
        while(isLeft(ha[b], hb[a], hb[a+1]) <= 0)
        {
            a++;
        }
        while(isLeft(hb[a], ha[b], ha[b-1]) >= 0)
        {
            b--;
            done = false;
        }
    }
    int idxs[] = {a,b};
    return idxs;
}

Point *mergeHull(Point *ha, Point* hb, int ha_length)
{
    Point *merged_hull;



    return merged_hull;
}


void divideAndConquer(Point *points, int points_length)
{
    if(points_length > 3)
    {
        int ha_length = points_length/2;
        Point ha[ha_length];

        Point *hb;
        int hb_length = points_length/2;

        Point *convex_hull;

        if(points_length%2 == 0)
        {
            hb = new Point[hb_length];
        }
        else
        {
            hb_length++;
            hb = new Point[hb_length];
        }


        int b = 0;
        for(int i=0;i<points_length;i++)
        {
            if(i < points_length/2)
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

        // convex_hull = mergeHull(ha,hb,ha_length);
        /* Merge Hull HA and HB,
           compute Upper and Lower Tangents
           discard all points between these to tangents */
    }
    else
    {
        // return points;
    }



}

int main()
{
    Point ps[] = {Point(1,2), Point(2,2), Point(2,1), Point(1,1), Point(3,3)};
    int length = 5;
    divideAndConquer(ps,length);
    return 0;
}
