#ifndef SPIRAL_H
#define SPIRAL_H

#include <GL/glu.h>
#include <deque>
#include <math.h>

#define M_PI 3.14159265358979323846

class Spiral
{
private:
    GLubyte colorRoad[3];
    GLubyte colorBG[3];
    deque<float> cordY;
    float auxRot = 0;
    Textures *textures;
    void updSpiral(float speed);
    void drawMode(int mode, GLubyte color[3]);

public:
    Spiral(GLubyte colorRoad[3], GLubyte colorBG[3], Textures *textures);
    void draw(float speed);
};

#endif