#include <string>
#include <iostream>

#include "menuState.hpp"

using namespace std;

void MenuState::load()  {
	tex.load("C:/Users/Ben/Desktop/Storage/2-18-2023 Desktop Clean/Laptop 3-2-2021/Ben Correll/Desktop/Storage/SPRING.png");

	rp = RenderProgram("Sprite Program");
    rp.attachShader(GL_VERTEX_SHADER, "C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/resources/spriteShader.vert");
    rp.attachShader(GL_FRAGMENT_SHADER, "C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/resources/spriteShader.frag");
    rp.link();

	float data[16] = {
        0, 0, 0, 0,
        0, tex.size[1], 0, 1,
        tex.size[0], 0, 1, 0,
        tex.size[0], tex.size[1], 1, 1
    };
	int spriteAttribSizes[] = {4};

    rb = RenderBuffer(1, spriteAttribSizes, 16, data);
}
void MenuState::init()  {}
void MenuState::update(Window* window, Game* game)  {}
void MenuState::render(Window* window, Game* game)  {
	cam = Camera((int)window->getScreenSize().x, (int)window->getScreenSize().y);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	rp.use();
    rp.bindTexture(tex);

    cam.useViewMatrix(rp);

    rb.bind();
    rb.draw(0, 4);
}
void MenuState::unload()  {}