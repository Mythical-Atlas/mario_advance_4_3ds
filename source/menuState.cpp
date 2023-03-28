#include <string>
#include <iostream>

#include "windows.h"
#include "psapi.h"

#include "menuState.hpp"
#include "audio.hpp"

#define VERTS_SIZE 16

using namespace std;

void MenuState::load()  {
	rp = RenderProgram("Sprite Program");
    rp.attachShader(GL_VERTEX_SHADER, "resources/versatileShader.vert");
    rp.attachShader(GL_FRAGMENT_SHADER, "resources/versatileShader.frag");
    rp.link();

	mmtopbgtex.load("resources/main menu top.png");
    mmbotbgtex.load("resources/main menu bottom.png");
    mmtexttex.load("resources/main menu text.png");

    mmtopbg.init(&mmtopbgtex,   0, 0, 0, 400, 240,         0, 0);
    mmbotbg.init(&mmbotbgtex,   1, 0, 0, 320, 240,         40, 240);
    mmstart.init(&mmtexttex,    2, 0, 0 * 17, 107, 1 * 17, 95 + 40, 112 + 240);
    mmmap.init(&mmtexttex,      3, 0, 1 * 17, 107, 2 * 17, 95 + 40, 80 + 240);
    mmsettings.init(&mmtexttex, 4, 0, 2 * 17, 107, 3 * 17, 95 + 40, 112 + 240);
    mmexit.init(&mmtexttex,     5, 0, 3 * 17, 107, 4 * 17, 95 + 40, 144 + 240);
    mmmario.init(&mmtexttex,    6, 0, 4 * 17, 107, 5 * 17, 95 + 40, 96 + 240);
    mmluigi.init(&mmtexttex,    7, 0, 5 * 17, 107, 6 * 17, 95 + 40, 128 + 240);

    int attribSizes[2] = {2, 2};
    rb = RenderBuffer(2, attribSizes, 8 * VERTS_SIZE);

    float* tempPointer;
    rb.uploadData(0 * VERTS_SIZE, VERTS_SIZE, mmtopbg.getData(tempPointer));
    rb.uploadData(1 * VERTS_SIZE, VERTS_SIZE, mmbotbg.getData(tempPointer));
    rb.uploadData(2 * VERTS_SIZE, VERTS_SIZE, mmstart.getData(tempPointer));
    rb.uploadData(3 * VERTS_SIZE, VERTS_SIZE, mmmap.getData(tempPointer));
    rb.uploadData(4 * VERTS_SIZE, VERTS_SIZE, mmsettings.getData(tempPointer));
    rb.uploadData(5 * VERTS_SIZE, VERTS_SIZE, mmexit.getData(tempPointer));
    rb.uploadData(6 * VERTS_SIZE, VERTS_SIZE, mmmario.getData(tempPointer));
    rb.uploadData(7 * VERTS_SIZE, VERTS_SIZE, mmluigi.getData(tempPointer));
    delete(tempPointer);

    /*music = AudioStream("romfs/shortMusic.raw", SDL_MIX_MAXVOLUME, true);
	jump = AudioStream("romfs/grow.raw", SDL_MIX_MAXVOLUME, false);
	coin = AudioStream("romfs/coin.raw", SDL_MIX_MAXVOLUME, false);
	death = AudioStream("romfs/death.raw", SDL_MIX_MAXVOLUME, false);*/
}
void MenuState::init(Window* window, Game* game)  {
    cam.init(new int[2]{(int)window->getScreenSize().x, (int)window->getScreenSize().y});

    mixer.init();
    memset(&controller, 0, sizeof(Controller)); // could be done with a union in Controller

	/*mixer.addStream(&music);
	mixer.addStream(&jump);
	mixer.addStream(&coin);
	mixer.addStream(&death);

    music.start();*/

	menuIndex = 0;
	selectionIndex = 0;
    moveReady = false;
    selectReady = false;

    stateStartTime = steady_clock::now();
    frameStartTime = stateStartTime;

    debugPrintTimer = 0;
}
void MenuState::update(Window* window, Game* game)  {
    time_point<steady_clock> currentTime = steady_clock::now();
    dt = duration_cast<milliseconds>(currentTime - frameStartTime).count();
    frameStartTime = currentTime;
    timeSinceInit = duration_cast<milliseconds>(currentTime - stateStartTime).count();

    ticksSinceLastDebugPrint++;

    if(controller.start && selectReady) {
        if(menuIndex == 0) {
            menuIndex++;
            selectionIndex = 0;
        }
        else if(menuIndex == 1) {
            if(selectionIndex == 0) {
                menuIndex++;
                selectionIndex = 0;
            }
            else if(selectionIndex == 2) {
                menuIndex--;
                selectionIndex = 0;
            }
        }
        else if(menuIndex == 2) {
            if(selectionIndex == 0) {
                game->changeState(1);
            }
        }
    }
    if(controller.up && moveReady) {
        if(menuIndex == 1) {
            if(selectionIndex > 0) {selectionIndex--;}
            else {selectionIndex = 2;}
        }
        else if(menuIndex == 2) {
            if(selectionIndex > 0) {selectionIndex--;}
            else {selectionIndex = 1;}
        }
    }
    if(controller.down && moveReady) {
        if(menuIndex == 1) {
            if(selectionIndex < 2) {selectionIndex++;}
            else {selectionIndex = 0;}
        }
        else if(menuIndex == 2) {
            if(selectionIndex < 1) {selectionIndex++;}
            else {selectionIndex = 0;}
        }
    }

    moveReady = !controller.up && !controller.down;
    selectReady = !controller.start;
}
void MenuState::render(Window* window, Game* game)  { // TODO: layering using z position
    if(timeSinceInit - debugPrintTimer >= 1000) {
        PROCESS_MEMORY_COUNTERS_EX pmc;
        GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
		SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;

        float tickRate = (float)ticksSinceLastDebugPrint / (timeSinceInit - debugPrintTimer) * 1000.0f;

        cout << "Virtual memory used: " << virtualMemUsedByMe << " bytes" << endl;
        cout << "Tick rate: " << tickRate << " fps" << endl;

        ticksSinceLastDebugPrint = 0;
        while(timeSinceInit - debugPrintTimer >= 1000) {debugPrintTimer += 1000;}
    }

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rp.useViewMatrix(&cam);

    mmtopbg.render(&rp, &rb);
    mmbotbg.render(&rp, &rb);
    
    if(menuIndex == 0) {mmstart.render(&rp, &rb);}
    if(menuIndex == 1) {
        mmmap.render(&rp, &rb, selectionIndex == 0, 0);
        mmsettings.render(&rp, &rb, selectionIndex == 1, 0);
        mmexit.render(&rp, &rb, selectionIndex == 2, 0);
    }
    if(menuIndex == 2) {
        mmmario.render(&rp, &rb,selectionIndex == 0, 0);
        mmluigi.render(&rp, &rb,selectionIndex == 1, 0);
    }
}
void MenuState::unload() {
	mixer.unload();
    mmtopbgtex.unload();
    mmbotbgtex.unload();
    mmtexttex.unload();
    rb.destroy();
    rp.destroy();
}

void MenuState::handleEvent(SDL_Event* event) {controller.handleEvent(event);}