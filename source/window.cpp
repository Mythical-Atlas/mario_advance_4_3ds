#include "window.hpp"

#ifndef USE_OPENGL_4_3
#define OPENGL_VERSION_MINOR 6
#else
#define OPENGL_VERSION_MINOR 3
#endif

void Window::create(bool fullscreen, int screenWidth, int screenHeight, string windowTitle) {
    if(fullscreen) {window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);}
    else {window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);}
}

void Window::init(bool fullscreen, int screenWidth, int screenHeight, string windowTitle) {
    // Initialize SDL 
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {sdl_die("Couldn't initialize SDL");}
    atexit(SDL_Quit);
    SDL_GL_LoadLibrary(NULL); // Default OpenGL is fine.

    // Request an OpenGL 4.6 context (should be core)
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_VERSION_MINOR);
    // Also request a depth buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    // Request a debug context.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

    create(fullscreen, screenWidth, screenHeight, windowTitle);

    if(window == NULL) {sdl_die("Couldn't set video mode");}

    maincontext = SDL_GL_CreateContext(window);

    if(maincontext == NULL) {sdl_die("Failed to create OpenGL context");}

    // Check OpenGL properties
    cout << "OpenGL loaded" << endl;
    gladLoadGLLoader(SDL_GL_GetProcAddress);
    cout << "Vendor:   " << glGetString(GL_VENDOR) << endl;
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "Version:  " << glGetString(GL_VERSION) << endl;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

vec2 Window::getScreenSize() {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    return vec2(w, h);
}
bool Window::checkFullscreen() {return SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP;}

void Window::swap() {SDL_GL_SwapWindow(window);}

int Window::pollEvent(SDL_Event* event) {return SDL_PollEvent(event);}