//
// Created by 颜哲 on 2020/7/23.
//
#include <stdlib.h>
#include <stdio.h>

extern "C" {
#include <SDL2/SDL.h>
}
#define  BLOCK_SIZE 4096000
static size_t buff_len = 0;
static Uint8 *audio_buf = NULL;
static Uint8 *audio_pos = NULL;

void read_audio_data(void *udata, Uint8 *stream, int len) {
    if (buff_len == 0) {
        return;
    }
    SDL_memset(stream, 0, len);
    len = len < buff_len ? len : buff_len;
    SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);
    audio_pos += len;
    buff_len -= len;
}

int main() {
    char *path = "/Users/yanzhe/ffmpeg/ffmpeg_install/ffmpeg/bin/out.pcm";
    FILE *audioFile = NULL;
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        SDL_Log("初始化失败");
        return -1;
    }
    audioFile = fopen(path, "r");
    if (!audioFile) {
        goto _FAIL;
    }
    audio_buf = (Uint8 *) malloc(BLOCK_SIZE);
    SDL_AudioSpec spec;
    spec.freq = 44100;
    spec.channels = 2;
    spec.silence = 0;
    spec.format = AUDIO_S16SYS;
    spec.callback = read_audio_data;
    spec.userdata = NULL;
    SDL_OpenAudio(&spec, NULL);
    SDL_PauseAudio(0);

    do {
        buff_len = fread(audio_buf, 1, BLOCK_SIZE, audioFile);
        audio_pos = audio_buf;
        while (audio_pos < (audio_buf + buff_len)) {
            SDL_Delay(1);
        }
    } while (buff_len != 0);

    SDL_CloseAudio();
    _FAIL:
    if (audio_buf) {
        free(audio_buf);
    }
    if (audioFile) {
        fclose(audioFile);
    }
    SDL_Quit();
    return 0;
}
