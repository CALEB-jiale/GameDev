//
//  Ship.cpp
//  Sprite
//
//  Created by 叶子寻 on 24/12/2022.
//

#include "Ship.hpp"
#include "Game.hpp"
#include "AnimSpriteComponent.hpp"

Ship::Ship(Game* game) : Actor(game) {
    mRightSpeed = 0.0f;
    mDownSpeed = 0.0f;
    
    // 创建一个动画精灵组件
    AnimSpriteComponent* asc = new AnimSpriteComponent(this);
    std::vector<SDL_Texture*> anims = {
        game->GetTexture("/Users/lucas/Documents/School/计算机基础/C++/练习程序/game_dev/Sprite/Sprite/Assets/Ship01.png"),
        game->GetTexture("/Users/lucas/Documents/School/计算机基础/C++/练习程序/game_dev/Sprite/Sprite/Assets/Ship01.png"),
        game->GetTexture("/Users/lucas/Documents/School/计算机基础/C++/练习程序/game_dev/Sprite/Sprite/Assets/Ship01.png"),
        game->GetTexture("/Users/lucas/Documents/School/计算机基础/C++/练习程序/game_dev/Sprite/Sprite/Assets/Ship01.png"),
    };
    asc->SetAnimTextures(anims);
}

void Ship::UpdateActor(float deltaTime) {
    Actor::UpdateActor(deltaTime);
    
    // 基于速度和增量时间更新位置
    Vector2 pos = GetPosition();
    pos.x += mRightSpeed * deltaTime;
    pos.y += mDownSpeed * deltaTime;

    // 限制在屏幕左半部分
    float limitX = GetGame()->getWindowSize().x / 2;
    float limitY = GetGame()->getWindowSize().y - 25;
    
    if (pos.x < 25.0f) {
        pos.x = 25.0f;
    } else if (pos.x > limitX) {
        pos.x = limitX;
    }
    
    if (pos.y < 25.0f) {
        pos.y = 25.0f;
    } else if (pos.y > limitY) {
        pos.y = limitY;
    }
    
    SetPosition(pos);
}

void Ship::ProcessKeyboard(const uint8_t* state) {
    mRightSpeed = 0.0f;
    mDownSpeed = 0.0f;
    
    // 右/左
    if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]) {
        mRightSpeed += 250.0f;
    }
    if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]) {
        mRightSpeed -= 250.0f;
    }
    
    // 上/下
    if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]) {
        mDownSpeed += 300.0f;
    }
    if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP]) {
        mDownSpeed -= 300.0f;
    }
}

