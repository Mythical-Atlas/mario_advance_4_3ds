#include "animation.hpp"

#include <fstream>

Animation::Animation(string path) {
	string data;
    string line = "";
    ifstream fileStream(path, ios::in);

    if(!fileStream.is_open()) {
        fprintf(stderr, "Could not load JSON file\n");
        abort();
    }

    while(!fileStream.eof()) {
        getline(fileStream, line);
        data.append(line + "\n");
    }

    fileStream.close();

	document.Parse(data.c_str());

	for(int i = 0; i < document["frames"].Size(); i++) {
		cout << document["frames"][i].GetInt() << endl;
	}
}