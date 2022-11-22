#ifndef FINALROAD_H
#define FINALROAD_H

#include <GL/glu.h>
#include <deque>

using namespace std;

class FinalRoad
{
    private: 
        GLubyte colorRoad[3];
        GLubyte colorBG[3];
        deque<float> cordX;
        deque<float> cordY;
        void drawMode(int mode, GLubyte color[3]);
    
    public:
        FinalRoad(GLubyte colorRoad[3], GLubyte colorBG[3]);
        void draw();      
};

#endif