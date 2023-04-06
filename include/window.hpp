#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <iostream>

#define GLM_FORCE_RADIANS 1
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

using namespace std;
using namespace glm;

class Window {
private:
    //bool* fullscreen;
    //int* screenWidth;
    //int* screenHeight;
    //string* windowTitle;
    SDL_Window* window;
    SDL_GLContext maincontext;

    static void sdl_die(const char* message) {
        cout << message << ": " << SDL_GetError() << endl;
        abort();
    }

    static void APIENTRY openglCallbackFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
        (void)source;
        (void)type;
        (void)id; 
        (void)severity;
        (void)length;
        (void)userParam;

        cout << message << endl;
        if(severity == GL_DEBUG_SEVERITY_HIGH) {
            cout << "Aborting..." << endl;
            abort();
        }
    }
public:
    void create(bool fullscreen, int screenWidth, int screenHeight, string windowTitle);
    void init(bool fullscreen, int screenWidth, int screenHeight, string windowTitle);
    vec2 getScreenSize(); // could be better
    bool checkFullscreen();
    void swap();
    int pollEvent(SDL_Event* event);
};

#endif