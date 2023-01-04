//
//  Component.cpp
//  Sprite
//
//  Created by 叶子寻 on 24/12/2022.
//

#include "Component.hpp"
#include "Actor.hpp"

Component::Component(Actor* owner, int updateOrder) {
    mOwner = owner;
    mUpdateOrder = updateOrder;
    mOwner->AddComponent(this);
}

Component::~Component() {
    mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime) {}
