//
//  Asteroid.hpp
//  BasicPhysics
//
//  Created by 叶子寻 on 30/12/2022.
//

#ifndef Asteroid_hpp
#define Asteroid_hpp

#include "Actor.hpp"

class Asteroid : public Actor {
public:
    Asteroid(class Game* game);
    ~Asteroid();
    
    class CircleComponent* GetCircle() { return mCircle; }
    
private:
    class CircleComponent* mCircle;
    class SpriteComponent* sc;
    class MoveComponent* mc;
};

#endif /* Asteroid_hpp */
