#ifndef FUNNYTUNNEL_H
#define FUNNYTUNNEL_H

#include "../glm/vec3.hpp"
#include <deque>

using namespace std;

class FunnyTunnel{
    private:
        deque<float> cordY;
        deque<float> cordX;
        deque<float> cordZ;
        GLubyte colorTunnel[3];
        GLubyte colorBG[3];
        float auxRot = 0;
        void updTunnel(float speed);
        void drawMode(int mode, GLubyte color[3], float scale);
    public:
        FunnyTunnel(GLubyte colorTunnel[3], GLubyte colorBG[3]);
        void draw(float speed, int dist);
};

#endif
