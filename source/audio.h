#ifndef AUDIO_H
#define AUDIO_H

#define SAMPLERATE 16000
#define SAMPLESPERBUF SAMPLERATE / 60
#define BYTESPERSAMPLE 4

#define BUFFER_SIZE SAMPLESPERBUF * BYTESPERSAMPLE

typedef struct {
	char inputBuffer[BUFFER_SIZE];
	FILE* filePointer;
	bool fillBlock;
	u32* audioBuffer;
	ndspWaveBuf waveBuf[2];
	int fileEnd;
	int numLoops;
	bool allocated;
	int channel;
} AudioFile;

void fillBuffer(void* audioBuffer, char* inputBuffer, size_t size) {
	u32* dest = (u32*)audioBuffer;

	for (int i = 0; i < size; i++) {
		dest[i] = inputBuffer[i * 4 + 0] +
		         (inputBuffer[i * 4 + 1] << 8) + 
		         (inputBuffer[i * 4 + 2] << 16) + 
		         (inputBuffer[i * 4 + 3] << 24);
	}

	DSP_FlushDataCache(audioBuffer, size);
}

void openSoundFile(AudioFile* audioFile, char* path, int numLoops, int channel) {
	audioFile->filePointer = fopen(path, "r");
	if(audioFile->filePointer != NULL) {if(ferror(audioFile->filePointer) != 0) {printf("Error reading sound file");}}
	else {printf("Error reading sound file");}
	
	audioFile->audioBuffer = (u32*)linearAlloc(SAMPLESPERBUF * BYTESPERSAMPLE * 2);
	
	memset(audioFile->waveBuf, 0, sizeof(ndspWaveBuf) * 2);
	
	audioFile->waveBuf[0].data_vaddr = &audioFile->audioBuffer[0];
	audioFile->waveBuf[0].nsamples = SAMPLESPERBUF;
	audioFile->waveBuf[1].data_vaddr = &audioFile->audioBuffer[SAMPLESPERBUF];
	audioFile->waveBuf[1].nsamples = SAMPLESPERBUF;
	
	audioFile->numLoops = numLoops;
	audioFile->channel = channel;
	audioFile->allocated = 1;
}

/*size_t bytesRead = fread(audioFile->inputBuffer, sizeof(char), BUFFER_SIZE, audioFile->filePointer);
if(bytesRead < BUFFER_SIZE) {audioFile->fileEnd = 2;}*/

void playSound(AudioFile* audioFile) {
	rewind(audioFile->filePointer);
	audioFile->fillBlock = 0;
	
	fread(audioFile->inputBuffer, sizeof(char), BUFFER_SIZE, audioFile->filePointer);
	fillBuffer(audioFile->waveBuf[0].data_pcm16, audioFile->inputBuffer, audioFile->waveBuf[audioFile->fillBlock].nsamples);
	fread(audioFile->inputBuffer, sizeof(char), BUFFER_SIZE, audioFile->filePointer);
	fillBuffer(audioFile->waveBuf[1].data_pcm16, audioFile->inputBuffer, audioFile->waveBuf[audioFile->fillBlock].nsamples);
	fread(audioFile->inputBuffer, sizeof(char), BUFFER_SIZE, audioFile->filePointer);
	
	ndspChnWaveBufAdd(audioFile->channel, &audioFile->waveBuf[0]);
	ndspChnWaveBufAdd(audioFile->channel, &audioFile->waveBuf[1]);
}

void updateSound(AudioFile* audioFile) {
	if(audioFile->waveBuf[audioFile->fillBlock].status == NDSP_WBUF_DONE) {
		if((audioFile->fileEnd % 2) == 1) {audioFile->fileEnd++;}
		
		fillBuffer(audioFile->waveBuf[audioFile->fillBlock].data_pcm16, audioFile->inputBuffer, audioFile->waveBuf[audioFile->fillBlock].nsamples);
		size_t bytesRead = fread(audioFile->inputBuffer, sizeof(char), BUFFER_SIZE, audioFile->filePointer);
		
		if(bytesRead < BUFFER_SIZE) {
			rewind(audioFile->filePointer);
			audioFile->fileEnd++;
		}

		ndspChnWaveBufAdd(audioFile->channel, &audioFile->waveBuf[audioFile->fillBlock]);

		audioFile->fillBlock = !audioFile->fillBlock;
	}
}

void freeSound(AudioFile* audioFile) {
	fclose(audioFile->filePointer);
	linearFree(audioFile->audioBuffer);
	audioFile->allocated = 0;
}

#endif