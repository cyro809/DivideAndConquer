#include <iostream>
#include <algorithm>
#include <fstream>
#include <utility>
#include <vector>

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

bool comparePoints (const Point p1, const Point p2)
{
    if( p1.x < p2.x)
        return 1;
    else if(p1.x == p2.x){
        return (p1.y < p2.y);
    }
    return 0;
}

float isLeft (Point P0, Point P1, Point P2)
{
    return (P1.x - P0.x)*(P2.y - P0.y) - (P2.x - P0.x)*(P1.y - P0.y);
}

int Rtangent_PointPolyC( Point P, int n, vector<Point> V )
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

int Ltangent_PointPolyC( Point P, int n, vector<Point> V )
{
    // use binary search for large convex polygons
    int     a, b, c;            // indices for edge chain endpoints
    int     dnA, dnC;           // test for down direction of edges a and c

    // leftmost tangent = minimum for the isLeft() ordering
    // test if V[0] is a local minimum
    if (above(P, V[n-1], V[0]) && !below(P, V[1], V[0]))
        return 0;               // V[0] is the minimum tangent point

    for (a=0, b=n;;) {          // start chain = [0,n] with V[n] = V[0]
        c = (a + b) / 2;        // midpoint of [a,b], and 0<c<n
        dnC = below(P, V[c+1], V[c]);
        if (above(P, V[c-1], V[c]) && !dnC)
            return c;          // V[c] is the minimum tangent point

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

std::pair<int,int> lowerTangent(vector<Point> ha, vector<Point> hb)
{
    int a = ha.size()-2;
    //a = Ltangent_PointPolyC(hb[0], ha.size(), ha);
    int b = 0;
    //b = Rtangent_PointPolyC(ha[a], hb.size(), hb);
    bool done = false;

    while(!done)
    {
        done = true;
        while(isLeft(hb[b], ha[a], ha[a-1]) >= 0)
        {
            a--;
            if(a == 0) a = ha.size() - 1;
        }
        while(isLeft(ha[a], hb[b], hb[b+1]) <= 0)
        {
            b++;
            if(b == hb.size() - 1) b = 0;
            done = false;
        }
    }
    //int idxs[] = {a,b};
    std::pair<int,int> idxs(a,b);
    return idxs;
}

std::pair<int,int> higherTangent(vector<Point> ha, vector<Point> hb)
{
    int a;
    a = Rtangent_PointPolyC(hb[0], ha.size(), ha);
    int b;
    b = Ltangent_PointPolyC(ha[a], hb.size(), hb);
    bool done = false;
    while(!done)
    {
        done = true;

        while(isLeft(hb[b], ha[a], ha[a+1]) <= 0)
        {
            a++;
            if (a == ha.size() - 1) a = 0;
        }
        while(isLeft(ha[a], hb[b], hb[b-1]) >= 0)
        {
            b--;
            if (b == 0) b = hb.size() - 1;
            done = false;
        }
    }
    std::pair<int,int> idxs(a,b);
    return idxs;
}

vector<Point> convexHull(vector<Point> P)
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

vector<Point> mergeHull(vector<Point> ha, vector<Point> hb)
{
    std::vector<Point> hull;
    hull.reserve( ha.size() + hb.size()); // preallocate memory

    hull.insert( hull.end(), ha.begin(), ha.end() );
    hull.insert( hull.end(), hb.begin(), hb.end() );

    std::vector<Point> merged_hull = convexHull(hull);
    merged_hull.pop_back();
    return merged_hull;
}


vector<Point> divideAndConquer(vector<Point> points)
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
        cout<<"HA:"<<endl;
        for(int i=0;i<HA.size();i++) HA[i].print();

        HB = divideAndConquer(HB);
        cout<<"HB:"<<endl;
        for(int i=0;i<HB.size();i++) HB[i].print();
        S = mergeHull(HA,HB);
        cout<<endl;
        return S;
    }
    else
    {
        cout<<"S:"<<endl;
        for(int i=0;i<points.size();i++) points[i].print();
        cout<<endl;
        return points;
    }



}

int main()
{
    /* TESTE PARA DIVIDE AND CONQUER */

    ifstream inData("input.txt");
    int x,y;
    char delim;
    vector<Point> S;
    for(int i=0;i<30;i++)
    {
        inData>>x>>delim>>y;
        S.push_back(Point(x,y));
    }

    std::sort(S.begin(),S.end(), comparePoints);

    S = divideAndConquer(S);
    for(int i=0;i<S.size();i++) S[i].print();

    /* TESTE PARA DIVIDE AND CONQUER */
    // vector<Point> S = {Point(1,1), Point(2,2), Point(3,3), Point(4,3), Point(4,2), Point(5,1), Point(6,3), Point(7,4), Point(7,5), Point(8,2)};
    //
    // S = divideAndConquer(S);
    // cout<<endl;
    // cout<<"RESULT:"<<endl;
    // for(int i=0;i<S.size();i++) S[i].print();

    /* TESTES PARA DETECTAR TANGENTES INFERIOR E SUPERIOR */
//    vector<Point> ha = {Point(1,1), Point(2,2), Point(3,3), Point(4,2), Point(4,3), Point(1,1)};
//    vector<Point> hb = {Point(5,1), Point(6,3), Point(7,4), Point(7,5), Point(8,2), Point(5,1)};
//    int ha_length = 6;
//    int hb_length = 6;
//
//    std::pair<int,int> tangents_indexes = higherTangent(ha,hb);
//
//    cout<<"t_i [0] = "<<tangents_indexes.first<<endl;
//    cout<<"t_i [1] = "<<tangents_indexes.second<<endl;
//    ha[tangents_indexes.first].print();
//    hb[tangents_indexes.second].print();
    return 0;
}
