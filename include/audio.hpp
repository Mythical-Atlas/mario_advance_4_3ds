#ifndef AUDIO_H
#define AUDIO_H

#include <string>
#include <iostream>
#include <fstream>

#include <SDL2/SDL.h>

#define BUFFER_SIZE 1024 // in bytes

using namespace std;

// modify to make into a mixer
// list of filestreams (loaded at runtime?)
// list of attributes
// mix all active filestreams in callback
class AudioFile {
public:
    ifstream fileStream;
    SDL_AudioDeviceID device;
    uint8_t buffer[BUFFER_SIZE];

    static void queueAudio(void* userdata, uint8_t* stream, int length) {
        AudioFile* audioFile = (AudioFile*)userdata;

        memset(stream, 0, length);
        memset(audioFile->buffer, 0, BUFFER_SIZE);

        audioFile->fileStream.read((char*)audioFile->buffer, length);
        SDL_MixAudioFormat(stream, audioFile->buffer, AUDIO_S16, audioFile->fileStream.gcount(), SDL_MIX_MAXVOLUME);

        /*if(player->file.tellg() == -1 && player->file2.tellg() == -1) {
            player->file.clear();
            player->file.seekg(0, ios::beg);

            player->file2.clear();
            player->file2.seekg(0, ios::beg);

            SDL_PauseAudioDevice(player->device, 1);
        }*/
        if(audioFile->fileStream.tellg() == -1) {
            audioFile->fileStream.clear();
            audioFile->fileStream.seekg(0, ios::beg);
        }
    }

    void init() {
        SDL_Init(SDL_INIT_AUDIO);

        SDL_AudioSpec spec;
        SDL_zero(spec);
        spec.freq = 16000;
        spec.format = AUDIO_S16;
        spec.channels = 2;
        spec.samples = BUFFER_SIZE / sizeof(uint16_t) / spec.channels;
        spec.callback = &queueAudio;
        spec.userdata = this;

        device = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);

        file = ifstream("romfs/grow.raw", ios::binary);
        file2 = ifstream("romfs/shortMusic.raw", ios::binary);

        SDL_PauseAudioDevice(device, 0);
    }

    void unload() {SDL_CloseAudioDevice(device);}
};

#endif