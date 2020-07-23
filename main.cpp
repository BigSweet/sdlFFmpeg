#include <stdlib.h>
#include <stdio.h>

extern "C" {
#include <SDL2/SDL.h>
}

int main() {
    SDL_Window *window = NULL;
    SDL_Renderer *render = NULL;
    int quit = 1;
    SDL_Event sdlEvent;
    SDL_Texture *sdlTexture;
    SDL_Init(SDL_INIT_VIDEO);
    //创建一个window
    window = SDL_CreateWindow("SDL2 Window", 200, 200, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("failed create window");
        goto _EXIT;
    }
    //创建render渲染器
    render = SDL_CreateRenderer(window, -1, 0);
    if (!render) {
        printf("failed create render");
        goto _DWINDOW;
    }
//    //设置render的颜色
//    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
//    //每次都清理一下屏
//    SDL_RenderClear(render);
//    //更新纹理
//    SDL_RenderPresent(render);
    sdlTexture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 640, 480);
    if (!sdlTexture) {
        SDL_Log("fail create texture");
        goto _RENDER;
    }
    do {
        //等待用户事件
        SDL_PollEvent(&sdlEvent);
        switch (sdlEvent.type) {
            case SDL_QUIT:
                quit = 0;
                break;
            default:
                SDL_Log("event type is %d", sdlEvent.type);
        }
        SDL_Rect rect;
        rect.w = 30;
        rect.h = 30;
        rect.x = rand() % 600;
        rect.y = rand() & 450;
        //设置纹理指向 textture
        SDL_SetRenderTarget(render, sdlTexture);
        //设置背景是黑色
        SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
        SDL_RenderClear(render);
        //画一个方块
        SDL_RenderDrawRect(render, &rect);
        //设置方块的颜色
        SDL_SetRenderDrawColor(render, 255, 0, 0, 0);
        SDL_RenderFillRect(render, &rect);

        //重置指向
        SDL_SetRenderTarget(render, NULL);
        //赋值到GPU
        SDL_RenderCopy(render, sdlTexture, NULL, NULL);
        //刷新
        SDL_RenderPresent(render);

    } while (quit);
    _RENDER:
    SDL_DestroyTexture(sdlTexture);
    _DWINDOW:
    SDL_DestroyWindow(window);
    _EXIT:
    SDL_Quit();
    return 0;
}
