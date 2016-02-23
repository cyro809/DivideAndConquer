#include <iostream>
#include <utility>

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

int Rtangent_PointPolyC( Point P, int n, Point* V )
{
    // use binary search for large convex polygons
    int     a, b, c;            // indices for edge chain endpoints
    int     upA, dnC;           // test for up direction of edges a and c

    // rightmost tangent = maximum for the isLeft() ordering
    // test if V[0] is a local maximum
    if (below(P, V[1], V[0]) && !above(P, V[n-1], V[0]))
        return 0;               // V[0] is the maximum tangent point

    for (a=0, b=n;;) {          // start chain = [0,n] with V[n]=V[0]
        c = (a + b) / 2;        // midpoint of [a,b], and 0<c<n
        dnC = below(P, V[c+1], V[c]);
        if (dnC && !above(P, V[c-1], V[c]))
            return c;          // V[c] is the maximum tangent point

        // no max yet, so continue with the binary search
        // pick one of the two subchains [a,c] or [c,b]
        upA = above(P, V[a+1], V[a]);
        if (upA) {                       // edge a points up
            if (dnC)                         // edge c points down
                 b = c;                           // select [a,c]
            else {                           // edge c points up
                 if (above(P, V[a], V[c]))     // V[a] above V[c]
                     b = c;                       // select [a,c]
                 else                          // V[a] below V[c]
                     a = c;                       // select [c,b]
            }
        }
        else {                           // edge a points down
            if (!dnC)                        // edge c points up
                 a = c;                           // select [c,b]
            else {                           // edge c points down
                 if (below(P, V[a], V[c]))     // V[a] below V[c]
                     b = c;                       // select [a,c]
                 else                          // V[a] above V[c]
                     a = c;                       // select [c,b]
            }
        }
    }
}

int Ltangent_PointPolyC( Point P, int n, Point* V )
{
    // use binary search for large convex polygons
    int     a, b, c;            // indices for edge chain endpoints
    int     dnA, dnC;           // test for down direction of edges a and c

    // leftmost tangent = minimum for the isLeft() ordering
    // test if V[0] is a local minimum
    if (above(P, V[n-1], V[0]) && !below(P, V[1], V[0]))
        return 0;               // V[0] is the minimum tangent point
    int co = 0;
    for (a=0, b=n;;) {          // start chain = [0,n] with V[n] = V[0]
        c = (a + b) / 2;        // midpoint of [a,b], and 0<c<n
        dnC = below(P, V[c+1], V[c]);
        cout<<"above = "<<above(P, V[c-1], V[c])<<endl;
        cout<<"dnc = "<<dnC<<endl;
        if (above(P, V[c-1], V[c]) && !dnC)
            return c;          // V[c] is the minimum tangent point
        else if(co > 30)
            return 0;

        co++;
        // no min yet, so continue with the binary search
        // pick one of the two subchains [a,c] or [c,b]
        dnA = below(P, V[a+1], V[a]);
        if (dnA) {                       // edge a points down
            if (!dnC)                        // edge c points up
                 b = c;                           // select [a,c]
            else {                           // edge c points down
                 if (below(P, V[a], V[c]))     // V[a] below V[c]
                     b = c;                       // select [a,c]
                 else                          // V[a] above V[c]
                     a = c;                       // select [c,b]
            }
        }
        else {                           // edge a points up
            if (dnC)                         // edge c points down
                 a = c;                           // select [c,b]
            else {                           // edge c points up
                 if (above(P, V[a], V[c]))     // V[a] above V[c]
                     b = c;                       // select [a,c]
                 else                          // V[a] below V[c]
                     a = c;                       // select [c,b]
            }
        }
    }
}

std::pair<int,int> lowerTangent(Point *ha, Point* hb, int ha_length, int hb_length)
{
    int a;
    cout<<"kjakjakaja"<<endl;
    a = Ltangent_PointPolyC(hb[0], ha_length, ha);
    cout<<"a = "<<a<<endl;
    int b;
    b = Rtangent_PointPolyC(ha[a], hb_length, hb);
    cout<<"b = "<<b<<endl;
    bool done = false;
    int c = 0;

    while(!done || c < 50)
    {
        done = true;
        cout<<"inicio"<<endl;
        while(isLeft(hb[b], ha[a], ha[a-1]) >= 0)
        {
            a--;
            cout<<"soma a"<<endl;
        }
        while(isLeft(ha[a], hb[b], hb[b+1]) <= 0)
        {
            b++;
            done = false;
            cout<<"diminui b"<<endl;
        }
        c++;
        cout<<"fim"<<endl;
    }
    //int idxs[] = {a,b};
    std::pair<int,int> idxs(a,b);
    return idxs;
}

std::pair<int,int> higherTangent(Point *ha, Point* hb, int ha_length, int hb_length)
{
    int a;
    cout<<"antes a"<<endl;
    a = Rtangent_PointPolyC(hb[0], ha_length, ha);
    cout<<"a = "<<a<<endl;
    int b;
    b = Ltangent_PointPolyC(ha[a], hb_length, hb);
    cout<<"b = "<<b<<endl;
    bool done = false;
    int c = 0;
    while(!done || c < 50)
    {
        done = true;

        while(isLeft(hb[b], ha[a], ha[a+1]) <= 0)
        {
            a++;

        }
        while(isLeft(ha[a], hb[b], hb[b-1]) >= 0)
        {
            b--;
            done = false;

        }
        c++;

    }
    std::pair<int,int> idxs(a,b);
    return idxs;
}

Point *mergeHull(Point *ha, Point* hb, int ha_length)
{
    Point *merged_hull;



    return merged_hull;
}


void divideAndConquer(Point *points, int points_length)
{
    int lower_tangent_points[2];
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
        //lower_tangent_points = lowerTangent(ha,hb,ha_length);
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
    //Point ps[] = {Point(1,2), Point(2,2), Point(2,1), Point(1,1), Point(3,3)};
    //int length = 5;
    //divideAndConquer(ps,length);

    Point ha[] = {Point(1,1), Point(2,2), Point(3,3), Point(4,2), Point(1,1)};
    Point hb[] = {Point(5,1), Point(6,3), Point(7,4), Point(8,2), Point(5,1)};
    int ha_length = 5;
    int hb_length = 5;

    std::pair<int,int> tangents_indexes = higherTangent(ha,hb,ha_length, hb_length);

    cout<<"t_i [0] = "<<tangents_indexes.first<<endl;
    cout<<"t_i [1] = "<<tangents_indexes.second<<endl;
    ha[tangents_indexes.first].print();
    hb[tangents_indexes.second].print();
    return 0;
}
