//
//  Ship.hpp
//  Sprite
//
//  Created by 叶子寻 on 24/12/2022.
//

#ifndef Ship_hpp
#define Ship_hpp

#include "Actor.hpp"

class Ship : public Actor {
public:
    Ship(class Game* game);
    ~Ship();
    void UpdateActor(float deltaTime) override;
    void ActorInput(const uint8_t* keyState) override;
//    void ProcessKeyboard(const uint8_t* state);
//    float GetRightSpeed() const { return mRightSpeed; }
//    float GetDownSpeed() const { return mDownSpeed; }
    
private:
//    float mRightSpeed;
//    float mDownSpeed;
    float mLaserCooldown; // 冷却时间
    class SpriteComponent* sc;
    class InputComponent* ic;
};

#endif /* Ship_hpp */
