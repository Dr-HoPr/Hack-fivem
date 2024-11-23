#pragma once

#include "../sdk/sdk.h"
#include <Windows.h>
#include "../main/fivem-external.h"
#include "../overlay/overlay.h"



class i_esp {
public:
    static i_esp& esp();

    void esp_init();
    bool IsOnScreen(D3DXVECTOR2 coords);
    void start();
    void draw_skeleton(uintptr_t ped_base);
    void vehicleesp();
    bool ignoreped = true;
    bool ignoredead = true;

    bool box = false;
    bool heathbar = false;
    bool armorbar = false;
    bool distance = false;
    bool weapons = false;
    bool playerid = false;
    bool lines = false;

    bool skeleton = false;
    bool fixedesp = true;
    bool boxnormal = false;
    bool crosshair = false;

    std::vector<std::string> friends;

    ImColor boxcolor = (255, 255, 255);
    ImColor FovColor = (255, 255, 255);
    ImColor LineColor = (255, 255, 255);
    ImColor colorespon = ImColor(255, 255, 255);

    int distanceint = 100;
    int HealthBar_type = 0;
    int ArmorBar_type = 1;

};