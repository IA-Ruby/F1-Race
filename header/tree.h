#ifndef TREE_H
#define TREE_H

#include "../glm/vec3.hpp"
#include <vector>

using namespace std;
using namespace glm;

class Tree
{    
    private:
        GLubyte colorTree[3];
        vector<float> angleLeavesX;
        vector<float> angleLeavesZ; 
        int sizeTree;
        float widthTree;
        vec3 cordTree;
    
    public:
        Tree(GLubyte colorTree[3], vec3 cordTree);
        void draw();
        void setCordTree(vec3 cordTree);
        void setCordYTree(float cordTree);
        void setCordZTree(float cordTree);
        vec3 getCordTree();
};

#endif