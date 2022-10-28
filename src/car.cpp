#include "../header/car.h"
#include <GL/gl.h>
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

Car::Car(GLubyte colorCar[3], GLubyte colorOutline[3], glm::vec3 pos, float speed){
    for(int i=0; i<3; i++){
        this->colorCar[i] = colorCar[i];
        this->colorOutline[i] = colorOutline[i];
    }
    this->carPos = pos;
    this->speed = speed;
}

Car::Car(GLubyte colorCar[3], glm::vec3 pos, float speed){
    for(int i=0; i<3; i++){
        this->colorCar[i] = colorCar[i];
    }
    this->carPos = pos;
    this->speed = speed;
    switch(rand()%3){
        case 0: 
            colorOutline[0] = 246;
            colorOutline[1] = 44;
            colorOutline[2] = 180; 
            break;
        case 1: 
            colorOutline[0] = 54;
            colorOutline[1] = 186; 
            colorOutline[2] = 255;
            break;
        case 2: 
            colorOutline[0] = 255; 
            colorOutline[1] = 225; 
            colorOutline[2] = 131; 
            break;
    }
}

void Car::draw(int texId){
    glLineWidth(4.0f);
    drawMode(GL_LINE, colorOutline);
    glLineWidth(1.0f);
    drawMode(GL_FILL, colorCar);
}

void Car::drawMode(int mode, GLubyte color[3]){
    glPolygonMode(GL_FRONT_AND_BACK, mode);
    glPushMatrix();
        glTranslatef(carPos.x,carPos.y,carPos.z);
        glRotatef(rot,0,0,1); 
        glTranslatef(-carPos.x,-carPos.y,-carPos.z);    // Volta pra origem

        // Algumas variaveis pra ajudar no mapeamento do carro
        
        float   // Eixo X
                outX = 14.6, maxX = 13.25, midX = 5, medX = 10, tMaxX = 10, tMinX = 9.5,

                // Eixo Y
                maxY = 35, lowY = -30, medY = 21, midY = 9, mid2Y = 8, med2Y = 20, 
                tMaxY = -28, tMedY = -29, tMidY = -30, tLowY = -31, tMinY = -32,

                // Eixo Z
                maxZ = 15, lowZ = -1.5, dwnZ = 0,midZ = 6, medZ = 9, tMaxZ = 14, tMinZ = 13;

        // Atualização da variavel de rotação
        auxRot = auxRot + (0.25*speed);
        if(auxRot >= 360){ auxRot = (0.25*speed); }
        
        //  Rodas
        for(int i=-1; i<=1; i+=2){    
            for(int j=-1; j<=1; j+=2){
                glPushMatrix();
                    glTranslatef(carPos.x+(i*10),carPos.y+(j*15),carPos.z);
                    glColor3ubv(color);
                    if(i<0){
                        glRotatef(-90.f,0,1,0);
                        glRotatef(auxRot,0,0,1);
                    }else{
                        glRotatef(90.f,0,1,0);
                        glRotatef(-auxRot,0,0,1);
                    }
                    drawWheel(5.f,2.5f);
                glPopMatrix();
            }
        }
        
        glColor3ubv(color);
        //Buracos das Rodas
        if(mode == GL_FILL){
            for(int i=-1; i<=1; i+=2){    
                for(int j=-1; j<=1; j+=2){
                    glPushMatrix();
                        glTranslatef(carPos.x+(i*5),carPos.y+(j*15),carPos.z);
                        glScalef(6,6,6); 
                        if(i<0){
                            glRotatef(180.f,0,0,1);
                        }
                        glBegin(GL_QUAD_STRIP);
                            for(float angulo = 0; angulo <= 180; angulo += 20){
                                float y = cos(angulo*M_PI/180.0);
                                float z = sin(angulo*M_PI/180.0);
                                glVertex3f(  0, y, z);
                                glVertex3f(1.6, y, z);
                            }
                        glEnd();
                    glPopMatrix();
                }
            }
        }

        //Elevação do lado dos buracos das rodas
        for(int i=-1; i<=1; i+=2){    
            for(int j=-1; j<=1; j+=2){
                glPushMatrix();
                    glTranslatef(carPos.x+(i*5),carPos.y+(j*15),carPos.z);
                    glScalef(6,6,6); 
                    if(i<0){
                        glRotatef(180.f,0,0,1);
                    }
                    glBegin(GL_QUAD_STRIP);
                        for(float angulo = 0; angulo <= 180; angulo += 20){
                            float y = cos(angulo*M_PI/180.0);
                            float z = sin(angulo*M_PI/180.0);
                            glVertex3f(1.6,     y,      z);
                            glVertex3f(1.4, y*1.2,  z*1.2);
                        }
                    glEnd();
                glPopMatrix();
            }
        }

        glPushMatrix();
            glTranslatef(carPos.x,carPos.y,carPos.z);
            //Não é necessario criar savestate daqui pra frente já que não estou realizando transformações

            // Parte de baixo do carro
            glBegin(GL_QUADS);  glVertex3f(  midX, -medY, lowZ);      
                                glVertex3f(  midX,  medY, lowZ);
                                glVertex3f( -midX,  medY, lowZ);
                                glVertex3f( -midX, -medY, lowZ);    glEnd();
            
            glBegin(GL_QUADS);  glVertex3f(  maxX, -midY, lowZ);
                                glVertex3f(  maxX,  midY, lowZ);
                                glVertex3f(  midX,  midY, lowZ);
                                glVertex3f(  midX, -midY, lowZ);    glEnd();
            
            glBegin(GL_QUADS);  glVertex3f( -midX, -midY, lowZ);
                                glVertex3f( -midX,  midY, lowZ);
                                glVertex3f( -maxX,  midY, lowZ);
                                glVertex3f( -maxX, -midY, lowZ);    glEnd();

            glBegin(GL_QUADS);  glVertex3f(  maxX,  lowY, lowZ);      
                                glVertex3f(  maxX, -medY, lowZ);
                                glVertex3f( -maxX, -medY, lowZ);
                                glVertex3f( -maxX,  lowY, lowZ);    glEnd();

            glBegin(GL_QUADS);  glVertex3f(  maxX,  maxY, lowZ);      
                                glVertex3f(  maxX,  medY, lowZ);
                                glVertex3f( -maxX,  medY, lowZ);
                                glVertex3f( -maxX,  maxY, lowZ);    glEnd();

            for(int i = -1; i <= 1; i+=2){
                for(int j = -1; j <= 1; j+=2){
                    // Preencher os buracos
                    if(mode == GL_FILL){
                        glBegin(GL_QUADS);  glVertex3f(  midX*i,  midY*j, dwnZ);     
                                            glVertex3f(  midX*i,  midY*j, lowZ);
                                            glVertex3f(  outX*i,  midY*j, lowZ);
                                            glVertex3f(  outX*i,  midY*j, dwnZ);    glEnd();

                        glBegin(GL_QUADS);  glVertex3f(  midX*i,  medY*j, dwnZ);     
                                            glVertex3f(  midX*i,  medY*j, lowZ);
                                            glVertex3f(  outX*i,  medY*j, lowZ);
                                            glVertex3f(  outX*i,  medY*j, dwnZ);    glEnd();
                    }
                    // Complemento do relevo
                    glBegin(GL_QUADS);  glVertex3f( (maxX+0.1)*i, (medY+1.2)*j, dwnZ);
                                        glVertex3f( (maxX+0.1)*i, (medY+1.2)*j, lowZ);
                                        glVertex3f(       outX*i,       medY*j, lowZ);
                                        glVertex3f(       outX*i,       medY*j, dwnZ);    glEnd();

                    glBegin(GL_TRIANGLES);  glVertex3f( (maxX+0.1)*i, (medY+1.2)*j, lowZ);
                                            glVertex3f( (maxX+0.1)*i,       medY*j, lowZ);
                                            glVertex3f(       outX*i,       medY*j, lowZ);   glEnd();

                    glBegin(GL_QUADS);  glVertex3f( (maxX+0.1)*i, (midY-1.2)*j, dwnZ);
                                        glVertex3f( (maxX+0.1)*i, (midY-1.2)*j, lowZ);
                                        glVertex3f(       outX*i,       midY*j, lowZ);
                                        glVertex3f(       outX*i,       midY*j, dwnZ);    glEnd();

                    glBegin(GL_TRIANGLES);  glVertex3f( (maxX+0.1)*i, (midY-1.2)*j, lowZ);
                                            glVertex3f( (maxX+0.1)*i,       midY*j, lowZ);
                                            glVertex3f(       outX*i,       midY*j, lowZ);   glEnd();
                    
                    // Tampar os buraco de dentro da parte das roda
                    glBegin(GL_QUADS);  glVertex3f(  midX*i,  midY*j, lowZ);
                                        glVertex3f(  midX*i,  medY*j, lowZ);
                                        glVertex3f(  midX*i,  medY*j, midZ);
                                        glVertex3f(  midX*i,  midY*j, midZ);    glEnd();
                }
            }
            
        //  Laterais
            //  Tras
            glBegin(GL_QUADS);  
            glEnable(GL_TEXTURE_2D);    glVertex3f(  maxX,  lowY, lowZ);    glTexCoord2f(0,0);    
                                        glVertex3f(  maxX,  lowY, medZ);    glTexCoord2f(1,0);      
                                        glVertex3f( -maxX,  lowY, medZ);    glTexCoord2f(1,1);
                                        glVertex3f( -maxX,  lowY, lowZ);    glTexCoord2f(0,1);  glDisable(GL_TEXTURE_2D);
                                                                                                glEnd();
            
            //  Frente
            glBegin(GL_QUADS);      
            glEnable(GL_TEXTURE_2D);    glVertex3f(  maxX,  maxY, lowZ);
                                        glVertex3f(  maxX,  maxY, midZ);
                                        glVertex3f( -maxX,  maxY, midZ);
                                        glVertex3f( -maxX,  maxY, lowZ);    glEnd();
                                                                            glDisable(GL_TEXTURE_2D);

            //Direita e Esquerda
            if(mode == GL_FILL){
                for(int i = -1; i<= 1; i+=2){
                    glBegin(GL_QUAD_STRIP);
                        glVertex3f(maxX*i, medY, lowZ);
                        glVertex3f(maxX*i, maxY, lowZ);
                        for(float angulo = 0; angulo <= 180; angulo += 20){
                            float y = cos(angulo*M_PI/180.0) * 6 + (medY + midY)/2;
                            float z = sin(angulo*M_PI/180.0) * 6 ;
                            if(angulo == 60){
                                glVertex3f(maxX*i,    y, z);
                                glVertex3f(maxX*i, maxY, midZ);
                            }else if(angulo == 80){
                                glVertex3f(maxX*i,    y, z);
                                glVertex3f(maxX*i, medY, medZ);
                            }else if(angulo == 100){
                                glVertex3f(maxX*i,    y, z);
                                glVertex3f(maxX*i, 0, medZ);
                            }else if(angulo < 60){
                                glVertex3f(maxX*i,    y, z);
                                glVertex3f(maxX*i, maxY, z);
                            }else{
                                glVertex3f(maxX*i, y, z);
                                glVertex3f(maxX*i, 0,    z);
                            }
                        }
                        glVertex3f(maxX*i, midY, lowZ);
                        glVertex3f(maxX*i, 0,    lowZ);
                    glEnd();
                    
                    glBegin(GL_QUAD_STRIP);
                        glVertex3f(maxX*i, -medY, lowZ);
                        glVertex3f(maxX*i, lowY, lowZ);
                        for(float angulo = 0; angulo <= 180; angulo += 20){
                            float y = cos(angulo*M_PI/180.0) * 6 + (medY + midY)/2;
                            float z = sin(angulo*M_PI/180.0) * 6 ;
                            if(angulo == 80){
                                glVertex3f(maxX*i,    -y, z);
                                glVertex3f(maxX*i, lowY, medZ);
                            }else if(angulo == 100){
                                glVertex3f(maxX*i,    -y, z);
                                glVertex3f(maxX*i, 0, medZ);
                            }else if(angulo < 80){
                                glVertex3f(maxX*i,    -y, z);
                                glVertex3f(maxX*i, lowY, z);
                            }else{
                                glVertex3f(maxX*i, -y, z);
                                glVertex3f(maxX*i, 0,    z);
                            }
                        }
                        glVertex3f(maxX*i, -midY, lowZ);
                        glVertex3f(maxX*i, 0,    lowZ);
                    glEnd();
            }
        }
            
        //   Meio
            //Traseira
            glBegin(GL_QUADS);  glVertex3f(  maxX,  lowY, medZ);
                                glVertex3f(  maxX, -medY, medZ);
                                glVertex3f( -maxX, -medY, medZ);
                                glVertex3f( -maxX,  lowY, medZ);    glEnd();

            glBegin(GL_QUADS);  glVertex3f(  maxX, -medY, medZ);
                                glVertex3f(  medX, -midY, maxZ);
                                glVertex3f( -medX, -midY, maxZ);
                                glVertex3f( -maxX, -medY, medZ);    glEnd();
                
            //Frente
            glBegin(GL_QUADS);  glVertex3f(  maxX,  maxY, midZ);
                                glVertex3f(  maxX,  medY, medZ);
                                glVertex3f( -maxX,  medY, medZ);
                                glVertex3f( -maxX,  maxY, midZ);    glEnd();

            glBegin(GL_QUADS);  glVertex3f(  medX,  midY, maxZ);
                                glVertex3f(  maxX,  medY, medZ);
                                glVertex3f( -maxX,  medY, medZ);
                                glVertex3f( -medX,  midY, maxZ);    glEnd();

            //Esqueda
            glBegin(GL_QUADS);  glVertex3f( -medX, -midY, maxZ);
                                glVertex3f( -medX,  midY, maxZ);
                                glVertex3f( -maxX,  medY, medZ);
                                glVertex3f( -maxX, -medY, medZ);    glEnd();
            //Direita
            glBegin(GL_QUADS);  glVertex3f(  medX, -midY, maxZ);
                                glVertex3f(  medX,  midY, maxZ);
                                glVertex3f(  maxX,  medY, medZ);
                                glVertex3f(  maxX, -medY, medZ);    glEnd();

        // Teto 
            glBegin(GL_QUADS);  glVertex3f(  medX, -midY, maxZ);      
                                glVertex3f(  medX,  midY, maxZ);
                                glVertex3f( -medX,  midY, maxZ);
                                glVertex3f( -medX, -midY, maxZ);    glEnd();    
        
        // Tail
            for(int i = -1; i<=1; i+=2){
                glBegin(GL_QUADS);  glVertex3f( tMaxX*i,  tMedY, medZ);
                                    glVertex3f( tMaxX*i,  tMidY, tMinZ);
                                    glVertex3f( tMinX*i,  tMidY, tMinZ);
                                    glVertex3f( tMinX*i,  tMedY, medZ); glEnd();

                glBegin(GL_QUADS);  glVertex3f( tMaxX*i,  tMaxY, medZ);
                                    glVertex3f( tMaxX*i,  tMedY, tMinZ);
                                    glVertex3f( tMinX*i,  tMedY, tMinZ);
                                    glVertex3f( tMinX*i,  tMaxY, medZ); glEnd();

                glBegin(GL_QUADS);  glVertex3f( tMaxX*i,  tMedY, medZ);
                                    glVertex3f( tMaxX*i,  tMaxY, medZ);
                                    glVertex3f( tMaxX*i,  tMedY, tMinZ);
                                    glVertex3f( tMaxX*i,  tMidY, tMinZ); glEnd();

                glBegin(GL_QUADS);  glVertex3f( tMinX*i,  tMedY, medZ);
                                    glVertex3f( tMinX*i,  tMaxY, medZ);
                                    glVertex3f( tMinX*i,  tMedY, tMinZ);
                                    glVertex3f( tMinX*i,  tMidY, tMinZ); glEnd();
            }

            glBegin(GL_QUADS);  glVertex3f(  maxX,  tMedY, tMaxZ);
                                glVertex3f(  maxX,  tMinY, tMaxZ);
                                glVertex3f( -maxX,  tMinY, tMaxZ);
                                glVertex3f( -maxX,  tMedY, tMaxZ); glEnd();
            
            glBegin(GL_QUADS);  glVertex3f(  maxX,  tMaxY, tMinZ);
                                glVertex3f(  maxX,  tLowY, tMinZ);
                                glVertex3f( -maxX,  tLowY, tMinZ);
                                glVertex3f( -maxX,  tMaxY, tMinZ); glEnd();

            glBegin(GL_QUADS);  glVertex3f(  maxX,  tMaxY, tMinZ);
                                glVertex3f(  maxX,  tMedY, tMaxZ);
                                glVertex3f(  maxX,  tMinY, tMaxZ);
                                glVertex3f(  maxX,  tLowY, tMinZ); glEnd();

            glBegin(GL_QUADS);  glVertex3f( -maxX,  tMaxY, tMinZ);
                                glVertex3f( -maxX,  tMedY, tMaxZ);
                                glVertex3f( -maxX,  tMinY, tMaxZ);
                                glVertex3f( -maxX,  tLowY, tMinZ); glEnd();

            glBegin(GL_QUADS);  glVertex3f( -maxX,  tLowY, tMinZ);
                                glVertex3f(  maxX,  tLowY, tMinZ);
                                glVertex3f(  maxX,  tMinY, tMaxZ);
                                glVertex3f( -maxX,  tMinY, tMaxZ); glEnd();

            glBegin(GL_QUADS);  glVertex3f( -maxX,  tMaxY, tMinZ);
                                glVertex3f(  maxX,  tMaxY, tMinZ);
                                glVertex3f(  maxX,  tMedY, tMaxZ);
                                glVertex3f( -maxX,  tMedY, tMaxZ); glEnd();
        glPopMatrix();
    glPopMatrix();
}

void Car::drawWheel(float radius, float width){
    float widthAux = width+0.5;
    glBegin(GL_QUAD_STRIP);
        for(int i=0; i<12; i++){
            float angle = i * 2 * M_PI / 12;
            glVertex3f(cos(angle)*radius, sin(angle)*radius,-width);
            glVertex3f(cos(angle)*radius, sin(angle)*radius, width);
        }
        glVertex3f(cos(0)*radius, sin(0)*radius, -width);
        glVertex3f(cos(0)*radius, sin(0)*radius, width);
    glEnd();
    glBegin(GL_QUAD_STRIP);
        for(int i=0; i<12; i++){
            float angle = i * 2 * M_PI / 12;
            glVertex3f(cos(angle)*radius, sin(angle)*radius,width);
            glVertex3f(cos(angle)*(radius * 0.75), sin(angle)*(radius * 0.75), widthAux);
        }
        glVertex3f(cos(0)*radius, sin(0)*radius, width);
        glVertex3f(cos(0)*(radius * 0.75), sin(0)*(radius * 0.75), widthAux);
    glEnd();
    glBegin(GL_QUAD_STRIP);
        for(int i=0; i<12; i++){
            float angle = i * 2 * M_PI / 12;
            glVertex3f(cos(angle)*radius, sin(angle)*radius,-width);
            glVertex3f(cos(angle)*(radius * 0.75), sin(angle)*(radius * 0.75), -widthAux);
        }
        glVertex3f(cos(0)*radius, sin(0)*radius, -width);
        glVertex3f(cos(0)*(radius * 0.75), sin(0)*(radius * 0.75), -widthAux);
    glEnd();
    glBegin(GL_QUAD_STRIP);
        for(int i=0; i<12; i++){
            float angle = i * 2 * M_PI / 12;
            glVertex3f(cos(angle)*(radius * 0.75), sin(angle)*(radius * 0.75),-widthAux);
            glVertex3f(cos(angle)*(radius * 0.25), sin(angle)*(radius * 0.25), -widthAux);
        }
        glVertex3f(cos(0)*(radius * 0.75), sin(0)*(radius * 0.75), -widthAux);
        glVertex3f(cos(0)*(radius * 0.25), sin(0)*(radius * 0.25), -widthAux);
    glEnd();
    glBegin(GL_QUAD_STRIP);
        for(int i=0; i<12; i++){
            float angle = i * 2 * M_PI / 12;
            glVertex3f(cos(angle)*(radius * 0.25), sin(angle)*(radius * 0.25),-widthAux);
            glVertex3f(cos(angle)*(radius * 0.25), sin(angle)*(radius * 0.25),-widthAux*2);
        }
        glVertex3f(cos(0)*(radius * 0.25), sin(0)*(radius * 0.25), -widthAux);
        glVertex3f(cos(0)*(radius * 0.25), sin(0)*(radius * 0.25), -widthAux*2);
    glEnd();

    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
        //glVertex3f(0,0,width2);
        for(int i=0; i<12; i++){
            float angle = i * 2 * M_PI / 12;
            glVertex3f(cos(angle)*(radius * 0.75), sin(angle)*(radius * 0.75),widthAux);
        }
        glVertex3f(cos(0)*(radius * 0.75), sin(0)*(radius * 0.75), widthAux);
    glEnd();   
}

glm::vec3 Car::getCarPos(){
    return carPos;
}

void Car::setCarPos(float carPos){
    this->carPos.y = carPos;
}

float Car::getSpeed(){
    return speed; 
}