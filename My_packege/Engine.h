#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

#include "Graphics/LWindows.h"
#include "Graphics/LTexture.h"
#include "utils/LTimer.h"

class Engine
{
public:
    Engine();
    ~Engine();

    // 初始化整个引擎 目前包括 设置SDL 获取窗口 载入资源 
    bool init();

    // 关闭
    void close();

private:
    // 初始化Texutre
    bool loadMedia();
    // 释放所有资源
    void free();

private:
    // 处理输入
    void handleEvent(SDL_Event& e);

    //更新游戏内容
    void update(float deltaTime);

    // 渲染
    void draw();

    void LoadContent() {};

public:
    // 对外 只暴露run 让游戏运行
    void run();

private:
    LWindow m_Window;
    SDL_Renderer* m_Renderer;
    LTexture m_Texture;

    // main loop flag
    bool m_quit;
};