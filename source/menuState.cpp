#include <string>
#include <iostream>

#include "menuState.hpp"
#include "audio.hpp"

using namespace std;

void MenuState::load()  {
	rp = RenderProgram("Sprite Program");
    rp.attachShader(GL_VERTEX_SHADER, "resources/spriteShader.vert");
    rp.attachShader(GL_FRAGMENT_SHADER, "resources/spriteShader.frag");
    rp.link();

	mmtopbgtex.load("resources/main menu top.png");
    mmbotbgtex.load("resources/main menu bottom.png");
    mmtexttex.load("resources/main menu text.png");

    mmtopbg.init(&mmtopbgtex, new int[4]{0, 0, 400, 240}, new int[2]{0, 0});
    mmbotbg.init(&mmbotbgtex, new int[4]{0, 0, 320, 240}, new int[2]{40, 240});
    mmstart.init(&mmtexttex,    new int[4]{0, 0 * 17, 107, 1 * 17}, new int[2]{95 + 40, 112 + 240});
    mmmap.init(&mmtexttex,      new int[4]{0, 1 * 17, 107, 2 * 17}, new int[2]{95 + 40, 112 + 240});
    mmsettings.init(&mmtexttex, new int[4]{0, 2 * 17, 107, 3 * 17}, new int[2]{95 + 40, 112 + 240});
    mmexit.init(&mmtexttex,     new int[4]{0, 3 * 17, 107, 4 * 17}, new int[2]{95 + 40, 112 + 240});
    mmmario.init(&mmtexttex,    new int[4]{0, 4 * 17, 107, 5 * 17}, new int[2]{95 + 40, 112 + 240});
    mmluigi.init(&mmtexttex,    new int[4]{0, 5 * 17, 107, 6 * 17}, new int[2]{95 + 40, 112 + 240});

	int spriteAttribSizes[] = {4};
    rb = RenderBuffer(1, spriteAttribSizes, 8 * 16);

    rb.uploadData(0 * 16, 16, mmtopbg.getData());
    rb.uploadData(1 * 16, 16, mmbotbg.getData());
    rb.uploadData(2 * 16, 16, mmstart.getData());
    rb.uploadData(3 * 16, 16, mmmap.getData());
    rb.uploadData(4 * 16, 16, mmsettings.getData());
    rb.uploadData(5 * 16, 16, mmexit.getData());
    rb.uploadData(6 * 16, 16, mmmario.getData());
    rb.uploadData(7 * 16, 16, mmluigi.getData());

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
}
void MenuState::render(Window* window, Game* game)  { // TODO: layering using z position
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rp.useViewMatrix(&cam);

    /*sprite1.render(&rp, &rb, 0, 4);
    sprite2.render(&rp, &rb, 4, 4);
    sprite3.render(&rp, &rb, 8, 4);*/

    mmtopbg.render(&rp, &rb, 0 * 4, 4);
    mmbotbg.render(&rp, &rb, 1 * 4, 4);
    mmstart.render(&rp, &rb, 2 * 4, 4);
}
void MenuState::unload() {
	mixer.unload();
}

void MenuState::handleEvent(SDL_Event* event) {controller.handleEvent(event);}