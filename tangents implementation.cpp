std::pair<int,int> RRTangent(Point *ha, Point* hb, int ha_length, int hb_length)
{
    int a;
    cout<<"antes a"<<endl;
    a = Rtangent_PointPolyC(hb[0], ha_length, ha);
    cout<<"a = "<<a<<endl;
    int b;
    b = Rtangent_PointPolyC(ha[a], hb_length, hb);
    cout<<"b = "<<b<<endl;
    bool done = false;
    int c = 0;
    while(!done)
    {
        done = true;

        while(isLeft(hb[b], ha[a], ha[a+1]) <= 0)
        {
            a++;

        }
        while(isLeft(ha[a], hb[b], hb[b-1]) >= 0)
        {
            b++;
            done = false;

        }
        c++;

    }
    std::pair<int,int> idxs(a,b);
    return idxs;
}

std::pair<int,int> LLTangent(Point *ha, Point* hb, int ha_length, int hb_length)
{
    int a;
    cout<<"antes a"<<endl;
    a = Ltangent_PointPolyC(hb[0], ha_length, ha);
    cout<<"a = "<<a<<endl;
    int b;
    b = Ltangent_PointPolyC(ha[a], hb_length, hb);
    cout<<"b = "<<b<<endl;
    bool done = false;
    int c = 0;
    while(!done)
    {
        done = true;

        while(isLeft(hb[b], ha[a], ha[a+1]) >= 0)
        {
            a--;

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