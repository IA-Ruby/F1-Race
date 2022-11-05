#include "../header/spiral.h"
#include <GL/gl.h>
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

Spiral::Spiral(GLubyte colorTunnel[3], GLubyte colorBG[3]){
    for(int i=0; i<3; i++){
        this->colorRoad[i] = colorRoad[i];
    }
    for(int i=0; i<900; i++){
        cordY.push_back(i*100);
    }
}

void Spiral::draw(float speed){
    updRoad(speed);
    glPolygonMode(GL_FRONT_AND_BACK, mode);
    glPushMatrix();
        glTranslatef(0,0,90);
        for(int i=0; i<cordY.size()-1; i++){
            glPushMatrix();
                glScalef(100,1,100);
                glColor3ubv(color);
                glBegin(GL_QUAD_STRIP);    
                    for (float angulo = 0; angulo <= 360; angulo += 1){
                        float x = cos(angulo*M_PI/180.0);
                        float z = sin(angulo*M_PI/180.0);
                        glVertex3f(x,cordY[i]+(angulo*2),z);
                        glVertex3f(x,cordY[i+1]+((angulo+1)*2),z);
                    }
                glEnd();
            glPopMatrix();
        }
    glPopMatrix();
}

void Spiral::updRoad(float speed){
    for(int i=0; i<cordY.size(); i++){
        cordY[i] -= speed;
        if(cordY[i] <= -400){
            cordY.pop_front();
            cordY.push_back(cordY.back()+1000);
            i--;
        }
    }
}