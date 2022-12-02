#ifndef RETROROAD_H
#define RETROROAD_H

#include <GL/glu.h>
#include "../src/tree.cpp"
#include <math.h>
#include <deque>
#include <vector>
#include "driver.h"

using namespace std;

class RetroRoad
{
    private:
        Driver enemy;
        deque<vector<int>> cordZRight;
        deque<vector<int>> cordZLeft;
        deque<float> cordYField;
        deque<float> cordYRoad;
        deque<Tree> treesRight;
        deque<Tree> treesLeft;
        GLubyte colorRoad[3];
        GLubyte colorField[3];
        GLubyte colorBG[3];
        void drawRoad();
        void drawQuad(float x, float y);
        void drawMountains(int mode, GLubyte color[3]);
        void drawTrees();
        void drawTunnel(int mode, GLubyte color[3]);
        void updRoad(float speed);
        void initQueues();
        vector<int> randMountain();
    
    public:
        RetroRoad( GLubyte colorRoad[3], GLubyte colorField[3], GLubyte colorBack[3], Textures* textures);
        void draw(float speed);
        int updEnemy(float time, Driver &player);
};

#endif