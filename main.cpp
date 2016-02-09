#include <iostream>

using namespace std;

class Point
{
    public:
        Point(double px, double py){ x = px; y = py; }
        Point() {x = 0; y = 0; }
        void print(){ cout<<"("<<x<<","<<y<<")"<<endl; }
    private:
        double x;
        double y;

};

void divideAndConquer(Point *points, int points_length)
{
    if(points_length > 3)
    {
        int ha_length = points_length/2;
        Point ha[ha_length];
        Point *hb;

        int hb_length = points_length/2;
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

        /* Merge Hull HA and HB,
           compute Upper and Lower Tangents
           discard all points between these to tangents */
    }
    else
    {
        /* Compute Hull */
    }



}

int main()
{
    Point ps[] = {Point(1,2), Point(2,2), Point(2,1), Point(1,1), Point(3,3)};
    int length = 5;
    divideAndConquer(ps,length);
    return 0;
}
