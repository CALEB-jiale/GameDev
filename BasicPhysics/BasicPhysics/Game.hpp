//
//  Game.hpp
//  Sprite
//
//  Created by 叶子寻 on 24/12/2022.
//

#ifndef Game_hpp
#define Game_hpp

#include <vector>
#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Math.hpp"

// Game Class
class Game {
public:
    Game();
    
    // 初始化
    bool Initialize();
    
    // 游戏运行
    void RunLoop();
    
    // 关闭游戏
    void ShutDown();
    
    // 添加/删除 actor
    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    // 添加/删除 sprite
    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);
    
    // 通过 texture 名字返回对应的 SDL_Texture 指针
    SDL_Texture* GetTexture(const std::string& fileName);
    
    // 获取窗口尺寸
    Vector2 getWindowSize() const { return mWindowSize; }
    
    // 添加/删除陨石
    void AddAsteroid(class Asteroid* ast);
    void RemoveAsteroid(class Asteroid* ast);
    
    std::vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }
    
private:
    // 处理进程
    void ProcessInput();
    
    // 更新游戏
    void UpdateGame();
    
    // 生成输出
    void GenerateOutput();
    
    // 加载游戏世界中的 actor
    void LoadData();
    void UnloadData();
    
    // 从文件中加载 texture
    SDL_Texture* LoadTexture(const char* fileName);
    
    // 游戏窗口尺寸
    Vector2 mWindowSize;
    
    // 通过 SDL 创建窗体
    SDL_Window* mWindow;
    
    // 继续运行
    bool mIsRunning;
    
    // 渲染器
    SDL_Renderer* mRenderer;
    
    // 记录运行时间
    Uint32 mTicksCount;
    
    // 已加载的 textures
    std::unordered_map<std::string, SDL_Texture*> mTextures;
    
    // 游戏中的所有 actors
    std::vector<class Actor*> mActors;
    
    // 待定的 actors
    std::vector<class Actor*> mPendingActors;
    
    // 跟踪现在是否在更新 actor
    bool mUpdatingActors;
    
    // 绘制的所有 sprite components
    std::vector<class SpriteComponent*> mSprites;
    
    // 玩家控制的飞船
    class Ship* mShip;
    
    // 所有的陨石
    std::vector<class Asteroid*> mAsteroids;
};

#endif /* Game_hpp */
