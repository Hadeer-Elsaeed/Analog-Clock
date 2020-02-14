#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<math.h>
#include<dos.h>
#include<time.h>
#define PI 3.147

using namespace std;

class point
{
    private:
    int x;
    int y;


public:
    void setX(int _x)
    {
        x = _x;
    }

    void setY(int _y)
    {
        y = _y;
    }

    void setXY(int _x , int _y)
    {
        x = _x;
        y = _y;
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

     point()
     {
         x = 1;
         y =1 ;
     }

     point (int _xy)
     {
         x = y = _xy;
     }

     point(int _x , int _y)
     {
         x = _x;
         y = _y;
     }

};
class shape
{
    int  color;
public:
    shape()
    {

    }

    virtual void draw() =0;

};




class Circle : public shape
{
    int raduis;
    point p;

public:
    void setRaduis(int _raduis)
    {
        raduis = _raduis;
    }
    int getRaduis()
    {
        return raduis;
    }

    Circle()
    {

    }


    Circle(int _x , int _y , int _raduis): p(_x ,_y)
    {

          raduis = _raduis;

    }

    void draw()
    {

        circle(p.getX(),p.getY(),raduis);

    }


};


class linet :public shape
{
    point p3 ,p4 ;
public:
    linet()
    {

    }

    linet (int _x1,int _y1 , int _x2 ,int _y2):p3(_x1 ,_y1),p4(_x2 ,_y2)
    {

    }
    void draw()
    {

        line(p3.getX(),p3.getY(),p4.getX(),p4.getY());

    }
};

void myfun(shape * sh, int c )
{
    setcolor(c);
    sh ->draw();
}

void clockLayout();
void secHand();
void hrHand();
void minHand();
int maxx,maxy;

int main()
{
 int gdriver=DETECT,gmode,error;
 initgraph(&gdriver,&gmode,"c:\\tc\\bgi");

 while(1)
 {
  clockLayout();
  secHand();
  minHand();
  hrHand();
  Sleep(1000);                /* pausing the outputscreen for 1 sec */
  cleardevice();           /* clearing the previous picture of clock */
 }
 return 0;
}

void clockLayout()
{
 int i,x,y,r;
 float j;
 maxx=getmaxx();
 maxy=getmaxy();

/* printing a round ring with outer radius of 5 pixel */
 for(i=1;i<5;i++)
 {
  Circle c(maxx/2,maxy/2,120-i);
  myfun(&c ,1);
 }

  /* displaying a circle in the middle of clock */
 Circle c1(maxx/2,maxy/2,4);
 myfun(&c1,1);

 x=maxx/2+100;
 y=maxy/2;
 r=100;

/* marking the hours for every 30 degrees */
 for(j=PI/6;j<=(2*PI);j+=(PI/6))
 {
    Circle c2(x,y,5);
    myfun(&c2,9);
    x=(maxx/2)+r*cos(j);
    y=(maxy/2)+r*sin(j);

 }

 x=maxx/2+100;
 y=maxy/2;
 r=100;

 for(j=PI/30;j<=(2*PI);j+=(PI/30))
 {  /* marking the minutes for every 6 degrees */
  Circle c3(x,y,2);
  myfun(&c3,15);
  x=(maxx/2)+r*cos(j);
  y=(maxy/2)+r*sin(j);
 }

}
void secHand()
{
 int r=80;
 int x=maxx/2;
 int y=maxy/2;
 int sec;
 float O;

 maxx=getmaxx();
 maxy=getmaxy();

 time_t t = time(NULL);
 tm* timePtr = localtime(&t);                    /*getting the seconds in system clock */
 sec = timePtr->tm_sec;
 O = sec*(PI/30)-(PI/2);           /* determining the angle of the line with respect to vertical */

 linet l1(maxx/2,maxy/2,x+r*cos(O),y+r*sin(O));
 myfun(&l1,14);
}

void hrHand()
{
 int r=50,hr,minuit;
 int x,y;
 float O;

 maxx=getmaxx();
 maxy=getmaxy();

 x=maxx/2;
 y=maxy/2;


 time_t t = time(NULL);
 tm* timePtr = localtime(&t);                    /*getting the seconds in system clock */
 minuit = timePtr->tm_min;
 hr = timePtr->tm_hour;

 /* determining the angle of the line with respect to vertical */
 if(hr<=12)
    O=(hr*(PI/6)-(PI/2))+((minuit/12)*(PI/30));
 if(hr>12)
    O=((hr-12)*(PI/6)-(PI/2))+((minuit/12)*(PI/30));

 linet l2 (maxx/2,maxy/2,x+r*cos(O),y+r*sin(O));
 myfun(&l2 ,1);
}


void minHand()
{
 int r=60,minuit;
 int x,y;
 float O;

 maxx=getmaxx();
 maxy=getmaxy();
 x=maxx/2;
 y=maxy/2;

 time_t t = time(NULL);
 tm* timePtr = localtime(&t);                    /*getting the seconds in system clock */
 minuit = timePtr->tm_min;

 O=(minuit*(PI/30)-(PI/2)); /* determining the angle of the line with respect to vertical */
 linet l3(maxx/2,maxy/2,x+r*cos(O),y+r*sin(O));
 myfun(&l3,2);
}
