#ifndef TRAINTUNNEL_H
#define TRAINTUNNEL_H

#include "../glm/vec3.hpp"
#include <deque>

using namespace std;

class TrainTunnel
{
    private:
        deque<float> cordY;
        GLubyte colorRoad[3];
        GLubyte colorWall[3];
        GLubyte colorBG[3];
        void updTunnel(float speed);
        void drawMode(int mode, GLubyte color1[3], GLubyte color2[3]);

    public:
        TrainTunnel(GLubyte colorRoad[3], GLubyte colorWall[3], GLubyte colorBG[3]);
        void draw(float speed);
};

#endif
