#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller { // TODO: input buffering
public:
	bool left   : 1;
	bool right  : 1;
	bool up     : 1;
	bool down   : 1;
	bool a      : 1;
	bool b      : 1;
	bool r      : 1;
	bool l      : 1;
	bool start  : 1;
	bool select : 1;

    void handleEvent(union SDL_Event* event);
};

#endif