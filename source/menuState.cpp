#include <string>
#include <iostream>

#include "menuState.hpp"
#include "audio.hpp"

using namespace std;

void MenuState::load()  {
	tex1.load("resources/test.png");
    tex2.load("gfx/objects/1up.png");
    tex3.load("gfx/objects/coin0.png");

    sprite1.init(&tex1, new vec2[2]{vec2(0, 0), vec2(1, 1)});
    sprite2.init(&tex2, new vec2[2]{vec2(0, 0), vec2(1, 1)});
    sprite3.init(&tex3, new vec2[2]{vec2(0, 0), vec2(1, 1)});

	rp = RenderProgram("Sprite Program");
    rp.attachShader(GL_VERTEX_SHADER, "resources/spriteShader.vert");
    rp.attachShader(GL_FRAGMENT_SHADER, "resources/spriteShader.frag");
    rp.link();

	float data[16] = {
        0, 0, 0, 0,
        0, (float)tex1.size[1], 0, 1,
        (float)tex1.size[0], 0, 1, 0,
        (float)tex1.size[0], (float)tex1.size[1], 1, 1
    };
	int spriteAttribSizes[] = {4};

    music = AudioStream("romfs/shortMusic.raw", SDL_MIX_MAXVOLUME, true);
	jump = AudioStream("romfs/grow.raw", SDL_MIX_MAXVOLUME, false);
	coin = AudioStream("romfs/coin.raw", SDL_MIX_MAXVOLUME, false);
	death = AudioStream("romfs/death.raw", SDL_MIX_MAXVOLUME, false);
    
    rb = RenderBuffer(1, spriteAttribSizes, 16 * 3);
    rb.uploadData(0, 16, data);

    data[5] = (float)tex2.size[1];
    data[8] = (float)tex2.size[0];
    data[12] = (float)tex2.size[0];
    data[13] = (float)tex2.size[1];
    rb.uploadData(16, 16, data);

    data[5] = (float)tex3.size[1];
    data[8] = (float)tex3.size[0];
    data[12] = (float)tex3.size[0];
    data[13] = (float)tex3.size[1];
    rb.uploadData(32, 16, data);
}
void MenuState::init(Window* window, Game* game)  {
    cam.init(new int[2]{(int)window->getScreenSize().x, (int)window->getScreenSize().y});

    mixer.init();
    memset(&controller, 0, sizeof(Controller)); // could be done with a union in Controller

	mixer.addStream(&music);
	mixer.addStream(&jump);
	mixer.addStream(&coin);
	mixer.addStream(&death);

    music.start();
    
    sprite1.pos = vec2(0, 0);
    sprite2.pos = vec2(200, 500);
    sprite3.pos = vec2(500, 200);
}
void MenuState::update(Window* window, Game* game)  {
    if(controller.up) {sprite2.pos.y -= 0.1f;}
    if(controller.down) {sprite2.pos.y += 0.1f;}
    if(controller.left) {sprite2.pos.x -= 0.1f;}
    if(controller.right) {sprite2.pos.x += 0.1f;}
    
    if(controller.l) {sprite2.rotation -= 0.01f;}
    if(controller.r) {sprite2.rotation += 0.01f;}
    
    if(controller.b) {sprite2.scale.x += 0.01f;}
    if(controller.a) {sprite2.scale.y += 0.01f;}
}
void MenuState::render(Window* window, Game* game)  { // TODO: layering using z position
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rp.useViewMatrix(&cam);

    sprite1.render(&rp, &rb, 0, 4);
    sprite2.render(&rp, &rb, 4, 4);
    sprite3.render(&rp, &rb, 8, 4);
}
void MenuState::unload() {
	mixer.unload();
}

void MenuState::handleEvent(SDL_Event* event) {controller.handleEvent(event);}