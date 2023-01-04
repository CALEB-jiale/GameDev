//
//  Actor.hpp
//  Sprite
//
//  Created by 叶子寻 on 24/12/2022.
//

#ifndef Actor_hpp
#define Actor_hpp

#include <vector>
#include "Math.hpp"

class Actor {
public:
    enum State {
        EActive,    // Update 仅仅在 EActive 状态下更新角色
        EPaused,
        EDead       // EDead 代表游戏要移除角色
    };
    
    // 构造函数
    Actor(class Game* game);    // dependency injection
    
    // 析构函数
    virtual ~Actor();

    // 被 Game 调用的 Update 函数 (不被继承重写)
    void Update(float deltaTime);
    
    // 更新属于该 actor 的所有组件 (不被继承重写)
    void UpdateComponents(float deltaTime);
    
    // actor 特有更新代码 (可重写)
    virtual void UpdateActor(float deltaTime);

    // Getters/setters
    // 位置
    const Vector2& GetPosition() const { return mPosition; }
    void SetPosition(const Vector2& pos) { mPosition = pos; }
    
    // 大小
    float GetScale() const { return mScale; }
    void SetScale(float scale) { mScale = scale; }
    
    // 旋转角度
    float GetRotation() const { return mRotation; }
    void SetRotation(float rotation) { mRotation = rotation; }

    // 状态
    State GetState() const { return mState; }
    void SetState(State state) { mState = state; }

    class Game* GetGame() { return mGame; }
    
    // 方向向量，计算机中 y 轴向下，因此要加上负号
    Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

    // 添加/移除 组件
    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);
    
    // 被 Game 调用的 ProcessInput（不可重写）
    void ProcessInput(const uint8_t* keyState);
    // 特定 Actor 输入（可重写）
    virtual void ActorInput(const uint8_t* keyState);
    
private:
    // Actor的状态
    State mState;

    // 变形
    Vector2 mPosition;
    float mScale;       // 放缩
    float mRotation;    // 旋转，采用的是弧度，而不是角度

    std::vector<class Component*> mComponents;
    class Game* mGame;
};

#endif /* Actor_hpp */
