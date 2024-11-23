#pragma once

#include <Windows.h>
#include "../sdk/sdk.h"
#include "../main/fivem-external.h"


class i_aim {
public:
    static i_aim& aim();

    uintptr_t BestTarget();
    void aimbot(uintptr_t Ped);
    void MemoryAim(D3DXVECTOR3 point, uintptr_t Ped);
    void HookMemoryAim();


    void start();

    int fov = 80;
    int smooth = 2;
    int distance = 100;
    int aimbottype = 0;
    int predictionint = 0;
    
    bool enable = false;
    bool aimenable = false;
    bool memory = false;
    bool prediction = false;

    bool showfov = false;

    bool smooth4 = false; //Set to true if you want it to be on by default.

    bool ignoreped = true;
    bool ignoredeath = true;
    bool targetfriend = false;
    int boneid = 0;
    int aimkey = 0;

    

};
