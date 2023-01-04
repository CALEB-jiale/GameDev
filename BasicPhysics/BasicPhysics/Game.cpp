//
//  Game.cpp
//  Sprite
//
//  Created by 叶子寻 on 24/12/2022.
//

#include "Game.hpp"
#include "Actor.hpp"
#include "Ship.hpp"
#include "Asteroid.hpp"
#include "SpriteComponent.hpp"
#include "BGSpriteComponent.hpp"

Game::Game() {
    mWindowSize = Vector2(1024.0f, 768.0f);
    mWindow = nullptr;
    mRenderer = nullptr;
    mIsRunning = true;
    mTicksCount = 0;
}

bool Game::Initialize() {
    // 初始化 SDL 库
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0) {
        SDL_Log("不能初始化 SDL: %s", SDL_GetError());
        return false;
    }
    
    // 创建 SDL 窗体
    mWindow = SDL_CreateWindow("太空漫游",            // 标题
                               100,                 // 窗体左上角的 x 坐标
                               100,                 // 窗体左上角的 y 坐标
                               mWindowSize.x,       // 窗体宽度
                               mWindowSize.y,       // 窗体高度
                               0);                  // 标志位
    
    if (!mWindow) {
        SDL_Log("创建窗体失败: %s", SDL_GetError());
        return false;
    }
    
    // 创建渲染器
    mRenderer = SDL_CreateRenderer(mWindow, // 显示的窗口
                                   -1, // 用来指定驱动程序的索引，如果游戏有多个窗口，这可能是需要考虑的，不然的话采用 -1 由 SDL 来决定
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // 采用硬件加速 ｜ 保持刷新率一致
                                   );
    
    // 初始化 SDL 图像
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        SDL_Log("不能初始化SDL_image: %s", SDL_GetError());
        return false;
    }
    
    // 加载游戏世界中的 actor
    LoadData();
    
    // 初始化运行时间
    mTicksCount = SDL_GetTicks();
    
    // 完成初始化
    return true;
}

void Game::ShutDown() {
    // 销毁顺序与构造顺序相反
    UnloadData();
    IMG_Quit();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    SDL_Event event;
    
    // 有 event 在队列就一直循环
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                mIsRunning = false;
                break;
                
            default:
                break;
        }
    }
    
    // 获取键盘的状态
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    
    // 如果按了 Esc，结束循环
    if (keyState[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }
    
    // 处理输入
    mUpdatingActors = true;
    for (auto actor : mActors) {
        actor->ProcessInput(keyState);
    }
    mUpdatingActors = false;
}

void Game::UpdateGame() {
    // 等到与上一帧间隔 16 ms
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    
    // 增量时间是上一帧到现在的时间差
    // (转换成秒)
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    
    // 固定增量时间最大值
    if (deltaTime > 0.05f) {
      deltaTime = 0.05f;
    }
      
    // 更新运行时间(为下一帧)
    mTicksCount = SDL_GetTicks();
    
    // 更新所有 actor
    mUpdatingActors = true;
    for (auto actor : mActors) {
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;

    // 移动待定 actor 到 mActors
    for (auto pending : mPendingActors) {
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();

    // 添加 dead actor 到临时向量
    std::vector<Actor*> deadActors;
    for (auto actor : mActors) {
        if (actor->GetState() == Actor::EDead) {
            deadActors.emplace_back(actor);
        }
    }

    // 删除处于dead的actor（从mActors中移除)
    for (auto actor : deadActors) {
        delete actor;
    }
}

void Game::GenerateOutput() {
    // 设置背景颜色
    SDL_SetRenderDrawColor(mRenderer, 129, 216, 209, 255);

    // 清理后缓冲区
    SDL_RenderClear(mRenderer);

    // 绘制所有精灵组件
    for (auto sprite : mSprites) {
        sprite->Draw(mRenderer);
    }

    // 交换前后缓冲区
    SDL_RenderPresent(mRenderer);
}

SDL_Texture* Game::LoadTexture(const char* fileName) {
    // 从文件中加载 surface
    SDL_Surface* surf = IMG_Load(fileName);
    
    if (!surf) {
        SDL_Log("加载图像文件 %s 失败", fileName);
        return nullptr;
    }
    
    // 从 surface 创建 texture
    SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surf);
    SDL_FreeSurface(surf);
    if (!tex) {
        SDL_Log("%s surface 转换到 texture 失败!", fileName);
        return nullptr;
    }
    return tex;
}

SDL_Texture* Game::GetTexture(const std::string& fileName) {
    SDL_Texture* tex = nullptr;
    
    // texture 是否已经存在？
    auto iter = mTextures.find(fileName);
    if (iter != mTextures.end()) {
        // 已存在，直接返回
        tex = iter->second;
    } else {
        // 不存在，从文件中加载
        tex = LoadTexture(fileName.c_str());
        mTextures.emplace(fileName.c_str(), tex);
    }
    return tex;
}

void Game::AddActor(Actor* actor) {
    // 如果正在更新actor，就添加到待处理列表里
    if (mUpdatingActors) {
        mPendingActors.emplace_back(actor);
    } else {
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor* actor) {
    // 是否在待定 actor 中
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end()) {
        // 交换到尾部（避免复制)
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
//        mPendingActors.erase(iter);
    }
    
    // 是否在 actor 中
    iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end()) {
        // 交换到尾部（避免复制)
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
//        mActors.erase(iter);
    }
}

void Game::AddSprite(SpriteComponent* sprite) {
    // 在有序向量中找到插入点
    // (第一个比传入的sprite的order顺序大的元素)
    int myDrawOrder = sprite->GetDrawOrder();
    auto iter = mSprites.begin();
    for (; iter != mSprites.end(); ++iter)
    {
        if (myDrawOrder < (*iter)->GetDrawOrder()) {
            break;
        }
    }
    
    // 在迭代器之前插入
    mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
    // (不能交换，不然顺序就没了)
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}

void Game::UnloadData() {
    // 删除 actor
    // 因为 ~Actor 调用 RemoveActor，所以必须使用循环
    while (!mActors.empty()) {
        delete mActors.back();
    }
    
    // 销毁texture
    for (auto i : mTextures) {
        SDL_DestroyTexture(i.second);
    }
    mTextures.clear();
}

void Game::LoadData() {
    // 创建一个飞船 player
    mShip = new Ship(this);
    mShip->SetPosition(Vector2(mWindowSize.x/2, mWindowSize.y/2));
    mShip->SetRotation(Math::PiOver2);
//    mShip->SetScale(1.5f);
    
    // 创建行星
    const int kNumAsteroids = 20;
    for (int i = 0; i < kNumAsteroids; i++) {
        new Asteroid(this);
    }
}

void Game::AddAsteroid(Asteroid* ast) {
    mAsteroids.emplace_back(ast);
}

void Game::RemoveAsteroid(Asteroid* ast) {
    auto iter = std::find(mAsteroids.begin(), mAsteroids.end(), ast);
//    if (iter != mAsteroids.end()) {
//        mAsteroids.erase(iter);
//    }
    mAsteroids.erase(iter);
}

