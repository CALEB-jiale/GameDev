//
//  Ship.cpp
//  Sprite
//
//  Created by 叶子寻 on 24/12/2022.
//

#include "Ship.hpp"
#include "Game.hpp"
#include "Laser.hpp"
#include "AnimSpriteComponent.hpp"
#include "InputComponent.hpp"

Ship::Ship(Game* game) : Actor(game) {
//    mRightSpeed = 0.0f;
//    mDownSpeed = 0.0f;
    mLaserCooldown = 0.0f;
    sc = new SpriteComponent(this, 150);
    ic = new InputComponent(this);
    
    // 设置 Texture
    sc->SetTexture(game->GetTexture("Assets/Ship.png"));
    
    // 设置按键
    ic->SetForwardKey(SDL_SCANCODE_W);
    ic->SetBackKey(SDL_SCANCODE_S);
    ic->SetClockwiseKey(SDL_SCANCODE_A);
    ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
    ic->SetMaxForwardSpeed(300.0f);
    ic->SetMaxAngularSpeed(Math::TwoPi);
    
//    // 创建一个动画精灵组件
//    AnimSpriteComponent* asc = new AnimSpriteComponent(this);
//    std::vector<SDL_Texture*> anims = {
//        game->GetTexture("Assets/Ship01.png"),
//        game->GetTexture("Ship01.png"),
//        game->GetTexture("Assets/Ship01.png"),
//        game->GetTexture("Assets/Ship01.png"),
//    };
//    asc->SetAnimTextures(anims);
}

void Ship::UpdateActor(float deltaTime) {
    Actor::UpdateActor(deltaTime);
    mLaserCooldown -= deltaTime;
}

void Ship::ActorInput(const uint8_t* keyState) {
    if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f) {
        // 创建激光
        Laser* laser = new Laser(GetGame());
        laser->SetPosition(GetPosition());
        laser->SetRotation(GetRotation());

        // 设定冷却期
        mLaserCooldown = 0.5f;
    }
}

Ship::~Ship() {
    if (sc) delete sc;
    if (ic) delete ic;
}

