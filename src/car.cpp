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

void Car::draw(bool show){
    glLineWidth(4.0f);
    drawMode(GL_LINE, colorOutline, show);
    glLineWidth(1.0f);
    drawMode(GL_FILL, colorCar, show);
}

void Car::drawMode(int mode, GLubyte color[3], bool show){
    glPolygonMode(GL_FRONT_AND_BACK, mode);
    glPushMatrix();
        glTranslatef(carPos.x,carPos.y,carPos.z);
        glRotatef(rot,0,0,1); 
        glTranslatef(-carPos.x,-carPos.y,-carPos.z);    // Volta pra origem

        // Algumas variaveis pra me ajudar no mapeamento do carro

        float outX = 14.6;
        float maxX = 13.25;     // Valor maximo de X, ou largura maxima
        float midX = 5;         // Valor do meio doo X, importante para tampar o buraco das rodas
        float medX = 10;

        float maxY = 35;        // Valor maximo de Y, ou o ponto extremo da frente do carro
        float lowY = -30;       // Valor minimo de Y, ou o ponto extremo da traseira do carro
        float medY = 21;        // Valor entre o o meio de Y e o valor maximo de Y;
        float midY = 9;         // Valor do meio de Y,

        float mid2Y = 8;
        float med2Y = 20;
        
        float maxZ = 15;
        float lowZ = -1.5;      // Valor mais baixo de Z, ou seja, o fundo do carro, não considerando as rodas;
        float dwnZ = 0;         // Valor vaixo de Z, relativo as luzes e a alguns buracos
        float midZ = 6;         // Valor do meio de Z
        float medZ = 9;         // Base dos vidros

        float tailMaxY = -28;
        float tailMidY = -29;
        float tailLowY = -30;
        float tailTopLowY = -31;
        float tailTopMaxY = -32;

        float tailMaxX = 10;
        float tailLowX = 9.5;

        float tailMaxZ = 14;
        float tailMidZ = 13;

        // Atualização da variavel de rotação
        auxRot = auxRot + (0.25*speed);
        if(auxRot >= 360){ auxRot = (0.25*speed); }
        
        //  Rodas
        for(int i=-1; i<=1; i+=2){    
            for(int j=-1; j<=1; j+=2){
                glPushMatrix();
                    glTranslatef(carPos.x+(i*10),carPos.y+(j*15),carPos.z);
                    if(i<0){
                        glRotatef(-90.f,0,1,0);
                        glRotatef(auxRot,0,0,1);
                    }else{
                        glRotatef(90.f,0,1,0);
                        glRotatef(-auxRot,0,0,1);
                    }
                    drawWheel(5.f,2.5f,color);
                glPopMatrix();
                glColor3ubv(color);
            }
        }

        //Buracos das Rodas
        if(mode == GL_FILL || show){
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
                    if(mode == GL_FILL || show){
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
            glBegin(GL_QUADS);  glVertex3f(  maxX,  lowY, lowZ);
                                glVertex3f(  maxX,  lowY, medZ);
                                glVertex3f( -maxX,  lowY, medZ);
                                glVertex3f( -maxX,  lowY, lowZ);    glEnd();
            
            //  Frente
            glBegin(GL_QUADS);  glVertex3f(  maxX,  maxY, lowZ);
                                glVertex3f(  maxX,  maxY, midZ);
                                glVertex3f( -maxX,  maxY, midZ);
                                glVertex3f( -maxX,  maxY, lowZ);    glEnd();

            //Direita
            if(mode == GL_FILL || show){               
                glBegin(GL_QUAD_STRIP);
                    glVertex3f(maxX, medY, lowZ);
                    glVertex3f(maxX, maxY, lowZ);
                    for(float angulo = 0; angulo <= 180; angulo += 20){
                        float y = cos(angulo*M_PI/180.0) * 6 + (medY + midY)/2;
                        float z = sin(angulo*M_PI/180.0) * 6 ;
                        if(angulo == 60){
                            glVertex3f(maxX,    y, z);
                            glVertex3f(maxX, maxY, midZ);
                        }else if(angulo == 80){
                            glVertex3f(maxX,    y, z);
                            glVertex3f(maxX, medY, medZ);
                        }else if(angulo == 100){
                            glVertex3f(maxX,    y, z);
                            glVertex3f(maxX, 0, medZ);
                        }else if(angulo < 60){
                            glVertex3f(maxX,    y, z);
                            glVertex3f(maxX, maxY, z);
                        }else{
                            glVertex3f(maxX, y, z);
                            glVertex3f(maxX, 0,    z);
                        }
                    }
                    glVertex3f(maxX, midY, lowZ);
                    glVertex3f(maxX, 0,    lowZ);
                glEnd();
                
                glBegin(GL_QUAD_STRIP);
                    glVertex3f(maxX, -medY, lowZ);
                    glVertex3f(maxX, lowY, lowZ);
                    for(float angulo = 0; angulo <= 180; angulo += 20){
                        float y = cos(angulo*M_PI/180.0) * 6 + (medY + midY)/2;
                        float z = sin(angulo*M_PI/180.0) * 6 ;
                        if(angulo == 80){
                            glVertex3f(maxX,    -y, z);
                            glVertex3f(maxX, lowY, medZ);
                        }else if(angulo == 100){
                            glVertex3f(maxX,    -y, z);
                            glVertex3f(maxX, 0, medZ);
                        }else if(angulo < 80){
                            glVertex3f(maxX,    -y, z);
                            glVertex3f(maxX, lowY, z);
                        }else{
                            glVertex3f(maxX, -y, z);
                            glVertex3f(maxX, 0,    z);
                        }
                    }
                    glVertex3f(maxX, -midY, lowZ);
                    glVertex3f(maxX, 0,    lowZ);
                glEnd();
                
                //Esquerda
                glBegin(GL_QUAD_STRIP);
                    glVertex3f(-maxX, medY, lowZ);
                    glVertex3f(-maxX, maxY, lowZ);
                    for(float angulo = 0; angulo <= 180; angulo += 20){
                        float y = cos(angulo*M_PI/180.0) * 6 + (medY + midY)/2;
                        float z = sin(angulo*M_PI/180.0) * 6 ;
                        if(angulo == 60){
                            glVertex3f(-maxX,    y, z);
                            glVertex3f(-maxX, maxY, midZ);
                        }else if(angulo == 80){
                            glVertex3f(-maxX,    y, z);
                            glVertex3f(-maxX, medY, medZ);
                        }else if(angulo == 100){
                            glVertex3f(-maxX,    y, z);
                            glVertex3f(-maxX, 0, medZ);
                        }else if(angulo < 60){
                            glVertex3f(-maxX,    y, z);
                            glVertex3f(-maxX, maxY, z);
                        }else{
                            glVertex3f(-maxX, y, z);
                            glVertex3f(-maxX, 0,    z);
                        }
                    }
                    glVertex3f(-maxX, midY, lowZ);
                    glVertex3f(-maxX, 0,    lowZ);
                glEnd();
                
                glBegin(GL_QUAD_STRIP);
                    glVertex3f(-maxX, -medY, lowZ);
                    glVertex3f(-maxX, lowY, lowZ);
                    for(float angulo = 0; angulo <= 180; angulo += 20){
                        float y = cos(angulo*M_PI/180.0) * 6 + (medY + midY)/2;
                        float z = sin(angulo*M_PI/180.0) * 6 ;
                        if(angulo == 80){
                            glVertex3f(-maxX,    -y, z);
                            glVertex3f(-maxX, lowY, medZ);
                        }else if(angulo == 100){
                            glVertex3f(-maxX,    -y, z);
                            glVertex3f(-maxX, 0, medZ);
                        }else if(angulo < 80){
                            glVertex3f(-maxX,    -y, z);
                            glVertex3f(-maxX, lowY, z);
                        }else{
                            glVertex3f(-maxX, -y, z);
                            glVertex3f(-maxX, 0,    z);
                        }
                    }
                    glVertex3f(-maxX, -midY, lowZ);
                    glVertex3f(-maxX, 0,    lowZ);
                glEnd();
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
            glBegin(GL_QUADS);  glVertex3f(  tailMaxX,  tailMidY, medZ);
                                glVertex3f(  tailMaxX,  tailLowY, tailMidZ);
                                glVertex3f(  tailLowX,  tailLowY, tailMidZ);
                                glVertex3f(  tailLowX,  tailMidY, medZ); glEnd();

            glBegin(GL_QUADS);  glVertex3f(  tailMaxX,  tailMaxY, medZ);
                                glVertex3f(  tailMaxX,  tailMidY, tailMidZ);
                                glVertex3f(  tailLowX,  tailMidY, tailMidZ);
                                glVertex3f(  tailLowX,  tailMaxY, medZ); glEnd();

            glBegin(GL_QUADS);  glVertex3f(  tailMaxX,  tailMidY, medZ);
                                glVertex3f(  tailMaxX,  tailMaxY, medZ);
                                glVertex3f(  tailMaxX,  tailMidY, tailMidZ);
                                glVertex3f(  tailMaxX,  tailLowY, tailMidZ); glEnd();

            glBegin(GL_QUADS);  glVertex3f(  tailLowX,  tailMidY, medZ);
                                glVertex3f(  tailLowX,  tailMaxY, medZ);
                                glVertex3f(  tailLowX,  tailMidY, tailMidZ);
                                glVertex3f(  tailLowX,  tailLowY, tailMidZ); glEnd();
            
            glBegin(GL_QUADS);  glVertex3f( -tailMaxX,  tailMidY, medZ);
                                glVertex3f( -tailMaxX,  tailLowY, tailMidZ);
                                glVertex3f( -tailLowX,  tailLowY, tailMidZ);
                                glVertex3f( -tailLowX,  tailMidY, medZ); glEnd();

            glBegin(GL_QUADS);  glVertex3f( -tailMaxX,  tailMaxY, medZ);
                                glVertex3f( -tailMaxX,  tailMidY, tailMidZ);
                                glVertex3f( -tailLowX,  tailMidY, tailMidZ);
                                glVertex3f( -tailLowX,  tailMaxY, medZ); glEnd();

            glBegin(GL_QUADS);  glVertex3f( -tailMaxX,  tailMidY, medZ);
                                glVertex3f( -tailMaxX,  tailMaxY, medZ);
                                glVertex3f( -tailMaxX,  tailMidY, tailMidZ);
                                glVertex3f( -tailMaxX,  tailLowY, tailMidZ); glEnd();

            glBegin(GL_QUADS);  glVertex3f( -tailLowX,  tailMidY, medZ);
                                glVertex3f( -tailLowX,  tailMaxY, medZ);
                                glVertex3f( -tailLowX,  tailMidY, tailMidZ);
                                glVertex3f( -tailLowX,  tailLowY, tailMidZ); glEnd();
            
            //  
            glBegin(GL_QUADS);  glVertex3f(  maxX,     tailMidY, tailMaxZ);
                                glVertex3f(  maxX,  tailTopMaxY, tailMaxZ);
                                glVertex3f( -maxX,  tailTopMaxY, tailMaxZ);
                                glVertex3f( -maxX,     tailMidY, tailMaxZ); glEnd();
            
            glBegin(GL_QUADS);  glVertex3f(  maxX,     tailMaxY, tailMidZ);
                                glVertex3f(  maxX,  tailTopLowY, tailMidZ);
                                glVertex3f( -maxX,  tailTopLowY, tailMidZ);
                                glVertex3f( -maxX,     tailMaxY, tailMidZ); glEnd();

            glBegin(GL_QUADS);  glVertex3f(  maxX,     tailMaxY, tailMidZ);
                                glVertex3f(  maxX,     tailMidY, tailMaxZ);
                                glVertex3f(  maxX,  tailTopMaxY, tailMaxZ);
                                glVertex3f(  maxX,  tailTopLowY, tailMidZ); glEnd();

            glBegin(GL_QUADS);  glVertex3f( -maxX,     tailMaxY, tailMidZ);
                                glVertex3f( -maxX,     tailMidY, tailMaxZ);
                                glVertex3f( -maxX,  tailTopMaxY, tailMaxZ);
                                glVertex3f( -maxX,  tailTopLowY, tailMidZ); glEnd();

            glBegin(GL_QUADS);  glVertex3f( -maxX,  tailTopLowY, tailMidZ);
                                glVertex3f(  maxX,  tailTopLowY, tailMidZ);
                                glVertex3f(  maxX,  tailTopMaxY, tailMaxZ);
                                glVertex3f( -maxX,  tailTopMaxY, tailMaxZ); glEnd();

            glBegin(GL_QUADS);  glVertex3f( -maxX,  tailMaxY, tailMidZ);
                                glVertex3f(  maxX,  tailMaxY, tailMidZ);
                                glVertex3f(  maxX,  tailMidY, tailMaxZ);
                                glVertex3f( -maxX,  tailMidY, tailMaxZ); glEnd();
        glPopMatrix();
    glPopMatrix();
}

void Car::drawWheel(float radius, float width, GLubyte color[3]){
    float widthAux = width+0.5;
    glColor3ubv(color);
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