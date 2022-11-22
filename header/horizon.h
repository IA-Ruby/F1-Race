#ifndef HORIZON_H
#define HORIZON_H

#include <GL/glu.h>
#include "../glm/vec3.hpp"
#include <deque>
#include <vector>

#define M_PI 3.14159265358979323846

using namespace std;
using namespace glm;

class Horizon
{
    private:
        GLubyte colorSun[3];
        GLubyte colorLight[3];
        GLubyte colorStars[3];
        GLubyte colorBG[3];
        vec3 sunPos;
        vector<vec3> starCord;
        float scale;
        float rotCam;
        bool lines;
        bool city;
        void drawStars();
        void drawSun();
        void drawSunLines();
        void drawSunGlow();
        void drawSunFrontGlow();
        void drawCity();
        void drawGlowCity();
    
    public:
        Horizon(GLubyte colorSun[3],
                GLubyte colorLight[3],
                GLubyte colorStars[3],
                GLubyte colorBG[3],
                vec3 sunPos,
                float scale);
                
        void draw(vec3 camPos, bool lines, bool city);    
};

#endif