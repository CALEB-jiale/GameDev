//
//  SpriteComponent.cpp
//  Sprite
//
//  Created by 叶子寻 on 24/12/2022.
//

#include "SpriteComponent.hpp"
#include "Actor.hpp"
#include "Game.hpp"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder) : Component(owner) {
    mTexture = nullptr;
    mDrawOrder = drawOrder;
    mTexWidth = 0;
    mTexHeight = 0;
    mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
    mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer) {
    if (mTexture) {
        SDL_Rect r;
        // 根据比例放缩
        r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
        r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
        // 居中显示
        r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
        r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);
    
        // 绘制（必须把弧度转换成角度，并且调整方向）
        SDL_RenderCopyEx(renderer,      // the rendering context
                         mTexture,      // the source texture
                         nullptr,       // the source SDL_Rect structure or NULL for the entire texture
                         &r,            // the destination SDL_Rect structure or NULL for the entire rendering target
                         -Math::ToDegrees(mOwner->GetRotation()),   // 旋转角度，负号表示逆时针方向
                         nullptr,       // 旋转中心，若为 NULL 则绕中心旋转
                         SDL_FLIP_NONE); // 弹跳类型
    }
}

void SpriteComponent::SetTexture(SDL_Texture* texture) {
    mTexture = texture;
    // 设置 宽度/高度
    SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}

