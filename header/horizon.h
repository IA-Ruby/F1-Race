#ifndef HORIZON_H
#define HORIZON_H

#include "../glm/vec3.hpp"
#include <deque>
#include <vector>

using namespace std;

class Horizon{
    private:
        GLubyte colorSun[3];
        GLubyte colorLight[3];
        GLubyte colorStars[3];
        GLubyte colorBG[3];
        glm::vec3 sunPos;
        vector<glm::vec3> starCord;
        float scale;
        float rotCam;
        void drawStars();
        void drawSun();
        void drawSunLines();
        void drawGlow();
        void drawCity();
        void drawGlowCity();
    public:
        Horizon(    GLubyte colorSun[3], 
                    GLubyte colorLight[3],
                    GLubyte colorStars[3],
                    GLubyte colorBG[3], 
                    glm::vec3 sunPos,
                    float scale);
        void draw(glm::vec3 camPos);    
};

#endif