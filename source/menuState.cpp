#include <string>
#include <iostream>

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

    mmtopbg.init(&mmtopbgtex,   0, new int[4]{0, 0, 400, 240},         new int[2]{0, 0});
    mmbotbg.init(&mmbotbgtex,   1, new int[4]{0, 0, 320, 240},         new int[2]{40, 240});
    mmstart.init(&mmtexttex,    2, new int[4]{0, 0 * 17, 107, 1 * 17}, new int[2]{95 + 40, 112 + 240});
    mmmap.init(&mmtexttex,      3, new int[4]{0, 1 * 17, 107, 2 * 17}, new int[2]{95 + 40, 80 + 240});
    mmsettings.init(&mmtexttex, 4, new int[4]{0, 2 * 17, 107, 3 * 17}, new int[2]{95 + 40, 112 + 240});
    mmexit.init(&mmtexttex,     5, new int[4]{0, 3 * 17, 107, 4 * 17}, new int[2]{95 + 40, 144 + 240});
    mmmario.init(&mmtexttex,    6, new int[4]{0, 4 * 17, 107, 5 * 17}, new int[2]{95 + 40, 96 + 240});
    mmluigi.init(&mmtexttex,    7, new int[4]{0, 5 * 17, 107, 6 * 17}, new int[2]{95 + 40, 128 + 240});

    rb = RenderBuffer(2, new int[2]{2, 2}, 8 * VERTS_SIZE);

    rb.uploadData(0 * VERTS_SIZE, VERTS_SIZE, mmtopbg.getData());
    rb.uploadData(1 * VERTS_SIZE, VERTS_SIZE, mmbotbg.getData());
    rb.uploadData(2 * VERTS_SIZE, VERTS_SIZE, mmstart.getData());
    rb.uploadData(3 * VERTS_SIZE, VERTS_SIZE, mmmap.getData());
    rb.uploadData(4 * VERTS_SIZE, VERTS_SIZE, mmsettings.getData());
    rb.uploadData(5 * VERTS_SIZE, VERTS_SIZE, mmexit.getData());
    rb.uploadData(6 * VERTS_SIZE, VERTS_SIZE, mmmario.getData());
    rb.uploadData(7 * VERTS_SIZE, VERTS_SIZE, mmluigi.getData());

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
    
    /*sprite1.pos = vec2(0, 0);
    sprite2.pos = vec2(200, 500);
    sprite3.pos = vec2(500, 200);*/

	menuIndex = 0;
	selectionIndex = 0;
    moveReady = false;
    selectReady = false;
}
void MenuState::update(Window* window, Game* game)  {
    /*if(controller.up) {sprite2.pos.y -= 0.1f;}
    if(controller.down) {sprite2.pos.y += 0.1f;}
    if(controller.left) {sprite2.pos.x -= 0.1f;}
    if(controller.right) {sprite2.pos.x += 0.1f;}
    
    if(controller.l) {sprite2.rotation -= 0.01f;}
    if(controller.r) {sprite2.rotation += 0.01f;}
    
    if(controller.b) {sprite2.scale.x += 0.01f;}
    if(controller.a) {sprite2.scale.y += 0.01f;}*/

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rp.useViewMatrix(&cam);

    /*sprite1.render(&rp, &rb, 0, 4);
    sprite2.render(&rp, &rb, 4, 4);
    sprite3.render(&rp, &rb, 8, 4);*/

    mmtopbg.render(&rp, &rb);
    mmbotbg.render(&rp, &rb);
    
    if(menuIndex == 0) {mmstart.render(&rp, &rb);}
    if(menuIndex == 1) {
        mmmap.render(&rp, &rb, new int[2]{selectionIndex == 0, 0});
        mmsettings.render(&rp, &rb, new int[2]{selectionIndex == 1, 0});
        mmexit.render(&rp, &rb, new int[2]{selectionIndex == 2, 0});
    }
    if(menuIndex == 2) {
        mmmario.render(&rp, &rb, new int[2]{selectionIndex == 0, 0});
        mmluigi.render(&rp, &rb, new int[2]{selectionIndex == 1, 0});
    }
}
void MenuState::unload() {
	mixer.unload();
}

void MenuState::handleEvent(SDL_Event* event) {controller.handleEvent(event);}