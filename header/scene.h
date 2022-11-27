#ifndef SCENE_H
#define SCENE_H

#include "driver.h"
#include "camera.h"
#include "horizon.h"
#include "retroRoad.h"
#include "finalRoad.h"
#include "trainTunnel.h"
#include "funnyTunnel.h"
#include "spiral.h"

#include "../src/driver.cpp"
#include "../src/camera.cpp"
#include "../src/horizon.cpp"
#include "../src/retroRoad.cpp"
#include "../src/finalRoad.cpp"
#include "../src/trainTunnel.cpp"
#include "../src/funnyTunnel.cpp"
#include "../src/spiral.cpp"

class Scene
{
    private:
        Camera camera;
        Driver player;
        Horizon horizon, finalHorizon;
        RetroRoad retroRoad;
        TrainTunnel trainTunnel;
        FunnyTunnel funnyTunnel;
        Spiral spiral;
        FinalRoad final;
        int scene = 1;
        void setCamera(vec3 camPos, vec3 lookAt);
        void updEnemy(float time);

    public:
        Scene(GLubyte colorCar[3],
              GLubyte colorSun[3],
              GLubyte colorLight[3],
              GLubyte colorField[3],
              GLubyte colorBG[3],
              GLubyte colorRoad[3],
              int texId);

        void draw(float time);
        void manageEvents(float time, bool acl, bool nitro, bool brake, int direction);
        void setScene(int scene);
};

#endif