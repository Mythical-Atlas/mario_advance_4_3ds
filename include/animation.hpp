#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>

#include <rapidjson/document.h>

#include "graphics.hpp"

using namespace rapidjson;

class Animation {
public:
	Document document;
	string name;
	
	
	Animation(string path);
};

#endif