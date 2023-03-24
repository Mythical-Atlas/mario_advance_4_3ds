#ifndef AUDIO_H
#define AUDIO_H

#include <string>
#include <iostream>
#include <fstream>

#define BUFFER_SIZE 1024 // in bytes
#define MAX_AUDIO_STREAMS 5

using namespace std;

class AudioStream {
public:
    bool playing;
    ifstream fileStream;
    uint8_t volume;
    bool loop;

    AudioStream() {}
    AudioStream(string path, uint8_t volume, bool loop) {
        playing = false;
        fileStream = ifstream(path, ios::binary);
        this->volume = volume;
        this->loop = loop;
    }

    void unload() {fileStream.close();}

    void start() {
        playing = true;
        fileStream.clear();
        fileStream.seekg(0, ios::beg);
    }
    void pause() {playing = false;}
    void resume() {playing = true;}
    void stop() {
        playing = false;
        fileStream.clear();
        fileStream.seekg(0, ios::beg);
    }
};

class AudioMixer {
public:
    AudioStream* streams[MAX_AUDIO_STREAMS];
    SDL_AudioDeviceID device;
    uint8_t buffer[BUFFER_SIZE];

    static void queueAudio(void* userdata, uint8_t* buffer, int length) {
        AudioMixer* mixer = (AudioMixer*)userdata;

        memset(buffer, 0, length);
        memset(mixer->buffer, 0, BUFFER_SIZE);

        for(uint8_t i = 0; i < MAX_AUDIO_STREAMS; i++) {
            AudioStream* stream = mixer->streams[i];
            if(stream == nullptr || !stream->playing) {continue;}

            stream->fileStream.read((char*)mixer->buffer, length);
            SDL_MixAudioFormat(buffer, mixer->buffer, AUDIO_S16, stream->fileStream.gcount(), stream->volume/*SDL_MIX_MAXVOLUME*/);

            if(stream->fileStream.tellg() == -1) {
                if(stream->loop) {stream->start();}
                else {stream->stop();}
            }
        }
        //SDL_PauseAudioDevice(player->device, 1);
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

        fill_n(streams, MAX_AUDIO_STREAMS, nullptr);

        //fileStream = ifstream("romfs/shortMusic.raw", ios::binary);
        //file2 = ifstream("romfs/shortMusic.raw", ios::binary);

        SDL_PauseAudioDevice(device, 0);
    }

    void unload() {
        SDL_CloseAudioDevice(device);
        //fill_n(streams, MAX_AUDIO_STREAMS, nullptr);
    }

    bool addStream(AudioStream* stream) {
        for(uint8_t i = 0; i < MAX_AUDIO_STREAMS; i++) {
            if(streams[i] == nullptr) {
                streams[i] = stream;
                return false;
            }
        }
        return true;
    }

    void clearStreams() {fill_n(streams, MAX_AUDIO_STREAMS, nullptr);}
};

#endif