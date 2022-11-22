#ifndef TREE_H
#define TREE_H

#include <GL/glu.h>
#include "../glm/vec3.hpp"
#include <vector>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

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