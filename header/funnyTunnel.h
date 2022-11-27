#ifndef FUNNYTUNNEL_H
#define FUNNYTUNNEL_H

#include <GL/glu.h>
#include "../glm/vec3.hpp"
#include <deque>
#include <deque>

#define M_PI 3.14159265358979323846

using namespace std;

class FunnyTunnel
{
    private:
        deque<float> cordY;
        deque<float> obstacle[2];
        vector<float> star;
        GLubyte colorTunnel1[3];
        GLubyte colorTunnel2[3];
        GLubyte colorTunnel3[3];
        GLubyte colorBG[3];
        float auxRot = 0;
        int starCount = 0;
        void updTunnel(float speed);
        void drawMode(int mode, GLubyte color[3], float scale);
        void drawObstacle();
        void drawStar();
        void drawTunnel(float scale);
        void newObstacle();
    
    public:
        FunnyTunnel(GLubyte colorTunnel1[3], GLubyte colorTunnel2[3], GLubyte colorTunnel3[3], GLubyte colorBG[3]);
        void draw(float speed, int direction);
        int checkColision(float speed);
};

#endif
