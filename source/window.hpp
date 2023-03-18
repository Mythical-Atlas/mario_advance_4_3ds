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
#include <SDL.h>

using namespace std;

class Window {
private:
    //bool* fullscreen;
    //int* screenWidth;
    //int* screenHeight;
    //string* windowTitle;
    SDL_Window* window;
    SDL_GLContext maincontext;

public:
    static void sdl_die(const char* message) {
        cerr << message << ": " << SDL_GetError() << endl;
        abort();
    }

    static void APIENTRY openglCallbackFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
        (void)source;
        (void)type;
        (void)id; 
        (void)severity;
        (void)length;
        (void)userParam;

        cerr << message << endl;
        if(severity == GL_DEBUG_SEVERITY_HIGH) {
            cerr << "Aborting..." << endl;
            abort();
        }
    }

    void init(bool fullscreen, int screenWidth, int screenHeight, string windowTitle) {
        // Initialize SDL 
        if(SDL_Init(SDL_INIT_VIDEO) < 0) {sdl_die("Couldn't initialize SDL");}
        atexit(SDL_Quit);
        SDL_GL_LoadLibrary(NULL); // Default OpenGL is fine.

        // Request an OpenGL 4.6 context (should be core)
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        // Also request a depth buffer
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        // Request a debug context.
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

        // Create the window
        if(fullscreen) {window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);}
        else {window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);}

        if(window == NULL) {sdl_die("Couldn't set video mode");}

        maincontext = SDL_GL_CreateContext(window);

        if(maincontext == NULL) {sdl_die("Failed to create OpenGL context");}

        // Check OpenGL properties
        cout << "OpenGL loaded" << endl;
        gladLoadGLLoader(SDL_GL_GetProcAddress);
        cout << "Vendor:   " << glGetString(GL_VENDOR) << endl;
        cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
        cout << "Version:  " << glGetString(GL_VERSION) << endl;

        // Enable the debug callback
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(openglCallbackFunction, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);

        // Use/don't use v-sync
        SDL_GL_SetSwapInterval(0); // no vsync

        // Disable depth test and face culling.
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);

        int w;
        int h;
        SDL_GetWindowSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    }

    void swap() {SDL_GL_SwapWindow(window);}

    void pollEvent(SDL_Event* event) {SDL_PollEvent(event);}
};

#endif