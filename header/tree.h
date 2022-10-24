#ifndef TREE_H
#define TREE_H

#include "../glm/vec3.hpp"
#include <vector>

using namespace std;

class Tree{
    private:
        GLubyte colorTree[3];
        GLubyte colorLeaves[3];
        GLubyte colorWood[3];
        vector<float> angleLeavesX;
        vector<float> angleLeavesZ; 
        int sizeTree;
        float widthTree;
        float cordTree;
        void drawMode(int mode, GLubyte color1[3], GLubyte color2[3]);
    public:
        Tree(   GLubyte colorLeaves[3], 
                GLubyte colorWood[3], 
                GLubyte colorTree[3],
                float cordTree);
        void draw(bool show);
        void setCordTree(float cordTree);
        float getCordTree();
};

#endif