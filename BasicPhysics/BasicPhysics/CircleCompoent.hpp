//
//  CircleCompoent.hpp
//  BasicPhysics
//
//  Created by 叶子寻 on 03/01/2023.
//

#ifndef CircleCompoent_hpp
#define CircleCompoent_hpp

#include "Component.hpp"
#include "Math.hpp"

class CircleComponent : public Component {
public:
    CircleComponent(class Actor* owner);
    
    float GetRadius() const;
    void SetRadius(float radius) { mRadius = radius; }
    
    const Vector2& GetCenter() const;
    
private:
    float mRadius;
};

bool Intersect(const CircleComponent& a, const CircleComponent& b);

#endif /* CircleCompoent_hpp */
