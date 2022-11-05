#ifndef FIELD_H
#define FIELD_H

#include "../glm/vec3.hpp"
#include <deque>
#include <vector>
#include "tree.h"
#include "../src/tree.cpp"

using namespace std;

class Field{
    private:
        deque<vector<int>> cordZRight;
        deque<vector<int>> cordZLeft;
        deque<float> cordY;
        deque<Tree> treesRight;
        deque<Tree> treesLeft;
        GLubyte colorField[3];
        GLubyte colorBG[3];
        void drawMode(int mode, GLubyte color[3]);
        void drawTrees();
        void updField(float speed);
        void initQueues();
        vector<int> randMountain();
    public:
        Field( GLubyte colorField[3], GLubyte colorBack[3]);
        void draw(float speed);
};

#endif