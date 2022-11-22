#ifndef TRAINTUNNEL_H
#define TRAINTUNNEL_H

#include <GL/glu.h>
#include "../glm/vec3.hpp"
#include <deque>
#include <math.h>

#define M_PI 3.14159265358979323846

using namespace std;

class TrainTunnel
{
    private:
        deque<float> cordY;
        float distance = 0;
        float trainPos;
        GLubyte colorRoad[3];
        GLubyte colorWall[3];
        GLubyte colorBG[3];
        void updTunnel(float speed);
        void drawMode(int mode, GLubyte color1[3], GLubyte color2[3]);
        void drawTrain(float speed);
        
    public:
        TrainTunnel(GLubyte colorRoad[3], GLubyte colorWall[3], GLubyte colorBG[3]);
        void draw(float speed);
        float getTrainPos();
};

#endif
