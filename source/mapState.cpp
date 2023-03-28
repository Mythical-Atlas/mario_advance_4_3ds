#include <string>
#include <iostream>

#include "windows.h"
#include "psapi.h"

#include "mapState.hpp"
#include "audio.hpp"

#define VERTS_SIZE 16

using namespace std;

void MapState::load()  {
	rp = RenderProgram("Sprite Program");
    rp.attachShader(GL_VERTEX_SHADER, "resources/versatileShader.vert");
    rp.attachShader(GL_FRAGMENT_SHADER, "resources/versatileShader.frag");
    rp.link();

	botbgtex.load("resources/map bottom.png");
    maptex.load("resources/map top.png");
    ferntex.load("resources/map fern.png");
    icontex.load("resources/map icon.png");

    botbgsprite.init(&botbgtex, 0, new int[4]{0, 0, 320, 240}, new int[2]{40, 240});
    mapsprite.init(&maptex,     1, new int[4]{0, 0, 400, 240}, new int[2]{0, 0});
    fernsprite.init(&ferntex,   2, new int[4]{0, 0, 16, 16});
    iconsprite.init(&icontex,   3, new int[4]{0, 0, 8, 8});

    rb = RenderBuffer(2, new int[2]{2, 2}, 4 * VERTS_SIZE);

    rb.uploadData(0 * VERTS_SIZE, VERTS_SIZE, botbgsprite.getData());
    rb.uploadData(1 * VERTS_SIZE, VERTS_SIZE, mapsprite.getData());
    rb.uploadData(2 * VERTS_SIZE, VERTS_SIZE, fernsprite.getData());
    rb.uploadData(3 * VERTS_SIZE, VERTS_SIZE, iconsprite.getData());

    /*music = AudioStream("romfs/shortMusic.raw", SDL_MIX_MAXVOLUME, true);
	jump = AudioStream("romfs/grow.raw", SDL_MIX_MAXVOLUME, false);
	coin = AudioStream("romfs/coin.raw", SDL_MIX_MAXVOLUME, false);
	death = AudioStream("romfs/death.raw", SDL_MIX_MAXVOLUME, false);*/
}
void MapState::init(Window* window, Game* game)  {
    cam.init(new int[2]{(int)window->getScreenSize().x, (int)window->getScreenSize().y});

    mixer.init();
    memset(&controller, 0, sizeof(Controller)); // could be done with a union in Controller

	/*mixer.addStream(&music);
	mixer.addStream(&jump);
	mixer.addStream(&coin);
	mixer.addStream(&death);

    music.start();*/

	mapIndex = 0;
    moveReady = false;
    selectReady = false;

    stateStartTime = steady_clock::now();
    frameStartTime = stateStartTime;

    debugPrintTimer = 0;

    animTimer = 0;
    fernFrame[0] = 0; fernFrame[1] = 0;
    iconFrame[0] = 0; iconFrame[1] = 0;
}
void MapState::update(Window* window, Game* game)  {
    time_point<steady_clock> currentTime = steady_clock::now();
    dt = duration_cast<milliseconds>(currentTime - frameStartTime).count();
    frameStartTime = currentTime;
    timeSinceInit = duration_cast<milliseconds>(currentTime - stateStartTime).count();

    ticksSinceLastDebugPrint++;

    if(controller.start && selectReady) {}
    if(controller.up && moveReady) {
        if(mapIndex == 0) {mapIndex++;}
        else if(mapIndex == 5 || mapIndex == 7) {mapIndex--;}
    }
    if(controller.down && moveReady) {
        if(mapIndex == 1) {mapIndex--;}
        else if(mapIndex == 4 || mapIndex == 6) {mapIndex++;}
    }
    if(controller.left && moveReady) {
         if(mapIndex >= 2 && mapIndex <= 4) {mapIndex--;}
        else if(mapIndex == 5) {mapIndex++;}
    }
    if(controller.right && moveReady) {
        if(mapIndex >= 1 && mapIndex <= 3) {mapIndex++;}
        else if(mapIndex == 6) {mapIndex--;}
    }

    moveReady = !controller.up && !controller.down && !controller.left && !controller.right;
    selectReady = !controller.start;
}
void MapState::render(Window* window, Game* game)  { // TODO: layering using z position
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

    botbgsprite.render(&rp, &rb);
    mapsprite.render(&rp, &rb);

    int mapFerns[25 * 15] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    };

    if(timeSinceInit - animTimer >= 100) {
        fernFrame[0]++;
        iconFrame[0]++;

        if(fernFrame[0] > 3) {fernFrame[0] = 0;}
        if(iconFrame[0] > 2) {iconFrame[0] = 0;}

        while(timeSinceInit - animTimer >= 100) {animTimer += 100;}
    }

    for(int x = 0; x < 25; x++) {
        for(int y = 0; y < 15; y++) {
            if(mapFerns[x + y * 25]) {
                fernsprite.pos = vec2(x * 16, y * 16);
                fernsprite.render(&rp, &rb, fernFrame);
            }
        }
    }

    if(mapIndex == 0) {iconsprite.pos = vec2( 8 * 16 + 4, 6 * 16 + 4);}
    if(mapIndex == 1) {iconsprite.pos = vec2( 8 * 16 + 4, 4 * 16 + 4);}
    if(mapIndex == 2) {iconsprite.pos = vec2(10 * 16 + 4, 4 * 16 + 4);}
    if(mapIndex == 3) {iconsprite.pos = vec2(14 * 16 + 4, 4 * 16 + 4);}
    if(mapIndex == 4) {iconsprite.pos = vec2(17 * 16 + 4, 4 * 16 + 4);}
    if(mapIndex == 5) {iconsprite.pos = vec2(17 * 16 + 4, 7 * 16 + 4);}
    if(mapIndex == 6) {iconsprite.pos = vec2(12 * 16 + 4, 7 * 16 + 4);}
    if(mapIndex == 7) {iconsprite.pos = vec2(12 * 16 + 4, 9 * 16 + 4);}

    iconsprite.render(&rp, &rb, iconFrame);
}
void MapState::unload() {
	mixer.unload();
}

void MapState::handleEvent(SDL_Event* event) {controller.handleEvent(event);}