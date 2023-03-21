#ifndef AUDIO_H
#define AUDIO_H

#include <string>
#include <iostream>
#include <fstream>

#include <SDL2/SDL.h>

#define BUFFER_SIZE 102400

using namespace std;

class AudioPlayer {
public:
    ifstream file;
    ifstream file2;
    SDL_AudioDeviceID device;
    uint8_t buffer[BUFFER_SIZE];
    uint8_t buffer2[BUFFER_SIZE];

    static void queueAudio(void* userdata, uint8_t* stream, int length) {
        AudioPlayer* player = (AudioPlayer*)userdata;

        memset(stream, 0, length);
        memset(player->buffer, 0, BUFFER_SIZE);
        memset(player->buffer2, 0, BUFFER_SIZE);

        cout << player->file2.tellg() << endl;

        player->file.read((char*)player->buffer, length);
        player->file2.read((char*)player->buffer2, player->file.gcount());

        //if(player->file.gcount() < length) {memset(&(player->buffer[player->file.gcount()]), 0, length - player->file.gcount());}
        //if(player->file2.gcount() < length) {memset(&(player->buffer2[player->file2.gcount()]), 0, length - player->file2.gcount());}

        SDL_MixAudioFormat(stream, player->buffer, AUDIO_S16, player->file.gcount(), SDL_MIX_MAXVOLUME);
        SDL_MixAudioFormat(stream, player->buffer2, AUDIO_S16, player->file.gcount(), SDL_MIX_MAXVOLUME);

        /*if(player->file.gcount() >= player->file2.gcount()) {
            SDL_MixAudioFormat(player->buffer, player->buffer2, AUDIO_S16, player->file2.gcount(), SDL_MIX_MAXVOLUME);
            SDL_MixAudioFormat(stream, player->buffer, AUDIO_S16, player->file.gcount(), SDL_MIX_MAXVOLUME);
        }
        else {
            SDL_MixAudioFormat(player->buffer2, player->buffer, AUDIO_S16, player->file.gcount(), SDL_MIX_MAXVOLUME);
            SDL_MixAudioFormat(stream, player->buffer2, AUDIO_S16, player->file2.gcount(), SDL_MIX_MAXVOLUME);
        }*/

        cout << player->file2.gcount() << endl;

        if(player->file2.tellg() == -1) {
            cout << "eof reached" << endl;
            SDL_PauseAudioDevice(player->device, 1);
        }

        if(player->file.tellg() == -1) {
            cout << "sounds effect eof reached" << endl;

            player->file.clear();
            player->file.seekg(0, ios::beg);

            SDL_PauseAudioDevice(player->device, 1);
        }

        cout << "\n" << endl;
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
        file2 = ifstream("romfs/music11.raw", ios::binary);

        SDL_PauseAudioDevice(device, 0);
    }

    void unload() {SDL_CloseAudioDevice(device);}
};

#endif