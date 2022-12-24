//
//  AnimSpriteComponent.hpp
//  Sprite
//
//  Created by 叶子寻 on 24/12/2022.
//

#ifndef AnimSpriteComponent_hpp
#define AnimSpriteComponent_hpp

#include "SpriteComponent.hpp"
#include "Math.hpp"
#include <vector>

class AnimSpriteComponent : public SpriteComponent {
public:
    AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
    
    // 更新每帧动画 (被组件重写)
    void Update(float deltaTime) override;
    
    // 设置用于动画的 texture
    void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
    
    // 设置/读取 动画 FPS
    float GetAnimFPS() const { return mAnimFPS; }
    void SetAnimFPS(float fps) { mAnimFPS = fps; }
    
private:
    // 动画里的所有texture
    std::vector<SDL_Texture*> mAnimTextures;
    
    // 当前显示的帧
    float mCurrFrame;
    
    // 动画帧率，允许不同的 AnimSprite 使用不同的帧速，同时支持动态地加速或减速
    float mAnimFPS;
};

#endif /* AnimSpriteComponent_hpp */
