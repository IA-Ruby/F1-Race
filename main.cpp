#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

float speed = 0.0;
float turn = 0.0;
bool accelerate = false;
bool brake = false;

void cameraLol(){
    glTranslatef(turn,0,0);
}

void rectangle(float x, float y){
    glBegin(GL_QUADS);
        glVertex3f(-x/2, -y/2, 1);
        glVertex3f( x/2, -y/2, 1);
        glVertex3f( x/2,  y/2, 1);
        glVertex3f(-x/2,  y/2, 1);
    glEnd();
};

void speedMeter(){
    //a mimir
}

void player(){
    //top
    glPushMatrix();
        glTranslatef(0,-100,-2);
        glColor3f(1.f, 0.f, 0.f);
        rectangle(20,20);
        glPopMatrix(); 

    //back


    //weels
}

void railRoads(){
    //a mimir
}

void roadStrips(){
    glPushMatrix();
        glTranslatef(0,100,-29.8);
        glColor3f(1.f, 1.f, 1.f);  
        rectangle(10,30);
        glPopMatrix();

    glPushMatrix();
        glTranslatef(0,50,-29.8);
        glColor3f(1.f, 1.f, 1.f);  
        rectangle(10,30);
        glPopMatrix();

    glPushMatrix();
        glTranslatef(0,0,-29.8);
        glColor3f(1.f, 1.f, 1.f);  
        rectangle(10,30);
        glPopMatrix();

    glPushMatrix();
        glTranslatef(0,-50,-29.8);
        glColor3f(1.f, 1.f, 1.f);  
        rectangle(10,30); 
        glPopMatrix();

    glPushMatrix();
        glTranslatef(0,-100,-29.8);
        glColor3f(1.f, 1.f, 1.f);  
        rectangle(10,30);
        glPopMatrix();
}

void draw(){
    
    
    speedMeter();

    glRotatef(-30,1,0,0);
    player();
    
    cameraLol();

    //Sky
    glPushMatrix();
        glRotatef(30,1,0,0);
        glTranslatef(0,0,-50);
        glColor3f(0.f, 1.f, 1.f);  
        rectangle(1000,1000);
        glPopMatrix();

    //Grass    
    glPushMatrix();
        glTranslatef(0,-100,-30);
        glColor3f(0.f, 1.f, 0.f);  
        rectangle(1000,500);
        glPopMatrix();

    //Road
    glPushMatrix();
        glTranslatef(0,-100,-29.9);
        glColor3f(0.f, 0.f, 0.f);  
        rectangle(300,500);
        glPopMatrix();

    railRoads();
    roadStrips();
}

int main(){
    // Request a 24-bits depth buffer when creating the window
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;

    // Create the main window
    sf::Window window(sf::VideoMode(800, 560), "F1-Race",  sf::Style::Titlebar | sf::Style::Close, contextSettings);

    // Make it the active window for OpenGL calls
    window.setActive();

    // Set the color and depth clear values
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    //Alpha
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // Disable lighting and texturing
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    // Configure the viewport (the same size as the window)
    glViewport(0, 0, window.getSize().x, window.getSize().y);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
    glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);

    // Define a 3D cube (6 faces made of 2 triangles composed by 3 vertices)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Create a clock for measuring the time elapsed
    sf::Clock clock;

    // Start the game loop
    while (window.isOpen()){
        // Process events
        sf::Event ev;
        while (window.pollEvent(ev)){
            switch(ev.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch(ev.key.code){
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        case sf::Keyboard::Up:
                            //Speed up
                            break;
                        case sf::Keyboard::Down:
                            //Brake
                            break;
                        case sf::Keyboard::Right:
                            if(turn>-140)
                                turn -= 10;
                            
                            //Turn right
                            break;
                        case sf::Keyboard::Left:
                            if(turn<140)
                                turn += 10;
                            
                            //Turn left
                            break;
                        default:
                            //lower speed
                            break;
                    }
                break;
            }
        }

        // Clear the color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Apply some transformations to rotate the cube
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.f, 0.f, -200.f);
        // Draw the cube
        glDrawArrays(GL_TRIANGLES, 0, 36);

        draw();
        // Finally, display the rendered frame on screen
        window.display();
    }

    return 0;
}
