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
    void UpdateActor(float deltaTime) override;
    void ProcessKeyboard(const uint8_t* state);
    float GetRightSpeed() const { return mRightSpeed; }
    float GetDownSpeed() const { return mDownSpeed; }
    
private:
    float mRightSpeed;
    float mDownSpeed;
};

#endif /* Ship_hpp */
