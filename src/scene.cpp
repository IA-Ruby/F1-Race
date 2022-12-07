#include "../header/scene.h"

Scene::Scene(   GLubyte colorCar[3], GLubyte colorSun[3], GLubyte colorLight[3], GLubyte colorField[3], 
                GLubyte colorBG[3], GLubyte colorRoad[3])
:
    camera(),
    textures(),
    player( colorBG, colorCar, vec3(0,0,0), 200, &textures),
    
    //Scene 1
    retroRoad( colorRoad, colorField, colorBG, &textures),
    horizon( colorSun, colorLight, colorField, colorBG, vec3(0,39000,2000), 1800.f),

    //Scene 2
    trainTunnel( colorSun, colorField, colorBG, &textures),
    
    //Scene 3
    funnyTunnel( colorSun, colorField, colorLight, colorBG),

    //Scene 4
    spiral( colorRoad, colorBG),

    //Scene 5
    final( colorLight, colorBG),
    finalHorizon( colorSun, colorLight, colorField, colorBG, vec3(0,39500,0), 1800.f)    
{}

void Scene::draw(float time, Shader light)
{   
    if (scene == 1) 
    {
        light.use();

        switch(retroRoad.updEnemy(time, player))
        {
            case 1: player.colision(1); break;
            case 2: setScene(2); break;
        };

        player.setCarPos(vec3(  player.getCarPos().x + (player.getSpeed() * player.getDirection() / 100), 
                                player.getCarPos().y, 
                                player.getCarPos().z)); 

        light.setVec3("LightPos", 1.0f, 1.0f, 1.0f);

        if(player.getCarPos().x >  60.f) player.setCarPosX( 60.f);
        if(player.getCarPos().x < -60.f) player.setCarPosX(-60.f);

        setCamera(vec3(player.getCarPos().x, -300, 20), 
                  vec3(player.getCarPos().x, -299, 20));

        light.setVec3("ViewPos", camera.getCamPos());

        if(player.getCarPos().y == 0)
        {
            retroRoad.draw(player.getSpeed());
        } 
        else retroRoad.draw(0);

        player.draw();

        glUseProgram(0);
        
        horizon.draw(camera.getCamPos(), true, true);
    }
    else if (scene == 2)
    {
        player.setCarPos(vec3(player.getCarPos().x + (player.getSpeed() * player.getDirection())/100, 0, 0)); 
            
        if(player.getCarPos().x >  60.f) player.setCarPosX( 60.f);
        if(player.getCarPos().x < -60.f) player.setCarPosX(-60.f);

        setCamera(vec3(player.getCarPos().x, 10, 11), 
                  vec3(player.getCarPos().x, 11, 11));

        if(trainTunnel.getTrainPos() + player.getSpeed() >= 11)
        {
            trainTunnel.draw(player.getSpeed());
            player.draw();
        }
        else setScene(3);
    }  
    else if (scene == 3)
    {
        player.setCarPos(vec3(0,0,0));
        setCamera(vec3(0, - 300, 20), 
                  vec3(0, - 299, 20));

        switch(funnyTunnel.checkColision(player.getSpeed()))
        {
            case 1: 
                setScene(4); 
                break;
            case 2: 
                player.colision(1);
            default:
                funnyTunnel.draw(player.getSpeed(), player.getDirection());
                player.draw();
        } 
    } 
    else if (scene == 4)
    {
        if(camera.getCamPos().x > 20000)
        { 
            player.colision(1);
            setScene(5);
        }
        else
        {
            player.setCarPos(vec3(400,-70, 10)); 

            if(camera.getCamPos().x < 400) camera.setCamPosX(400); 

            setCamera(vec3( camera.getCamPos().x + player.getSpeed()/10, 10, 30), 
                      vec3( player.getCarPos()));

            spiral.draw(player.getSpeed());

            player.setCarRotX(-10);
            player.setCarRotZ(10);

            player.draw();

            player.setCarRotX(0);
            player.setCarRotZ(0);
        }
    }    
    else if (scene == 5)
    {
        player.setCarPos(vec3(0, player.getCarPos().y + player.getSpeed()/2, 0)); 

        setCamera(vec3(0, -300, 20), 
                  vec3(0, -299, 20));

        final.draw();
        finalHorizon.draw(camera.getCamPos(), false, false);
        player.draw();
    }
}

void Scene::setCamera(vec3 camPos, vec3 lookAt)
{
    camera.setCamPos(camPos);
    camera.setCamLookAt(lookAt);
    glMultMatrixf(value_ptr(camera.getCamera()));
}

void Scene::manageEvents(float time, bool acl, bool nitro, bool brake, int direction)
{   
    if (nitro)
    {
        player.turn(0);

        player.nitro(time);

        if (camera.getCamPos().y > -400)
        {
            camera.setCamPosY(camera.getCamPos().y - (100 * time));
        }
        if (camera.getCamPos().y < -400)
        {
            camera.setCamPosY(-400);
        }
    }
    else
    {
        player.turn(direction);

        if (camera.getCamPos().y < -300)
        {
            camera.setCamPosY(camera.getCamPos().y + (100 * time));
        }
        if (camera.getCamPos().y > -300)
        {
            camera.setCamPosY(-300);
        }

        if (acl)
        {
            if (player.getSpeed() >= 200)
            {
                player.slowDown(time);
            }
            else
            {
                player.speedUp(time);
            }
        }
        else if (brake)
        {
            player.brake(time);
        }
        else
        {
            player.slowDown(time);
        }
    }
}

void Scene::setScene(int scene)
{
    player.setCarPos(vec3(0,0,0));
    this->scene = scene;
}