#ifndef TREE_H
#define TREE_H

#include "../glm/vec3.hpp"
#include <vector>

using namespace std;

class Tree{
    private:
        GLubyte colorTree[3];
        vector<float> angleLeavesX;
        vector<float> angleLeavesZ; 
        int sizeTree;
        float widthTree;
        float cordTree;
    public:
        Tree(GLubyte colorTree[3], float cordTree);
        void draw();
        void setCordTree(float cordTree);
        float getCordTree();
};

#endif