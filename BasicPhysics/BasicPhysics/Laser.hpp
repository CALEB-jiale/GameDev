//
//  Laser.hpp
//  BasicPhysics
//
//  Created by 叶子寻 on 03/01/2023.
//

#ifndef Laser_hpp
#define Laser_hpp

#include "Actor.hpp"

class Laser : public Actor
{
public:
    Laser(class Game* game);
    ~Laser();

    void UpdateActor(float deltaTime) override;
    
private:
    float mDeathTimer;
    
    class CircleComponent* mCircle;
    class SpriteComponent* sc;
    class MoveComponent* mc;
};

#endif /* Laser_hpp */
