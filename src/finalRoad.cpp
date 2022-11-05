#include "../header/finalRoad.h"
#include <GL/gl.h>

FinalRoad::FinalRoad(GLubyte colorRoad[3], GLubyte colorBG[3]){
    for(int i = 0; i<3; i++) {
        this->colorRoad[i] = colorRoad[i];
        this->colorBG[i] = colorBG[i];

    }
    for(int i = -50; i<=100; i++){
        if(i<=50)
            cordX.push_back(i*20);
        if(i>=0)
            cordY.push_back(i*200);
    }
}

void FinalRoad::draw(float speed){
    updRoad(speed);
    drawMode(GL_LINE,colorRoad);
    drawMode(GL_FILL,colorBG);
}

void FinalRoad::drawMode(int mode, GLubyte color[3]){
    glPolygonMode(GL_FRONT_AND_BACK, mode);
    glPushMatrix();
        glColor3ubv(color);
        glTranslatef(0,0,-5.1);
        for(int i=0; i<(cordY.size()-1); i++){
            glBegin(GL_QUAD_STRIP);
            for(int j=-100; j<100; j++){
                glVertex3f( j*20, cordY[i],   0);
                glVertex3f( j*20, cordY[i+1], 0);
            }
            glEnd();
        }
    glPopMatrix();
}

void FinalRoad::updRoad(float speed){
    for(int i=0; i<cordY.size(); i++){
        cordY[i] -= speed;
        if(cordY[i]<-400.f){
            cordY.push_back(cordY[i] + (cordY.size()*200));
            cordY.pop_front();
            i--;
        }
    }
}