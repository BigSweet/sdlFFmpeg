cmake_minimum_required(VERSION 3.15)
project(sdlProject)
set(CMAKE_CXX_STANDARD 14)
set(FFMPEG_DIR /usr/local/ffmpeg)
include_directories(${FFMPEG_DIR}/include/) # 头文件搜索路径
link_directories(${FFMPEG_DIR}/lib/) # 动态链接库或静态链接库的搜索路径

# 声明一个变量SDL2_DIR为SDL2安装路径
set(SDL2_DIR /usr/local/Cellar/sdl2/2.0.12_1)
# 设置要包含的头文件的路径
include_directories(${SDL2_DIR}/include)
# 设置要关联的库的路径
link_directories(${SDL2_DIR}/lib)

add_executable(sdlProject main.cpp)
add_executable(sdlProject1 yuvVideo.cpp)
add_executable(sdlProject2 pcmPlay.cpp)
target_link_libraries(
        sdlProject
        avcodec
        avdevice
        avfilter
        avformat
        swresample
        avutil
        postproc
        swscale
        SDL2
        SDL2main
)
target_link_libraries(
        sdlProject1
        avcodec
        avdevice
        avfilter
        avformat
        swresample
        avutil
        postproc
        swscale
        SDL2
        SDL2main
)
target_link_libraries(
        sdlProject2
        avcodec
        avdevice
        avfilter
        avformat
        swresample
        avutil
        postproc
        swscale
        SDL2
        SDL2main
)