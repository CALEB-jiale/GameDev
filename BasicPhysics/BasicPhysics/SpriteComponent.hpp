//
//  SpriteComponent.hpp
//  Sprite
//
//  Created by 叶子寻 on 24/12/2022.
//

#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include <SDL2/SDL.h>
#include "Component.hpp"

class SpriteComponent : public Component {
public:
    // (越低的 order 对应越深的背面)
    SpriteComponent(class Actor* owner, int drawOrder = 100);
    ~SpriteComponent();

    virtual void Draw(SDL_Renderer* renderer);
    virtual void SetTexture(SDL_Texture* texture);

    int GetDrawOrder() const { return mDrawOrder; }
    int GetTexHeight() const { return mTexHeight; }
    int GetTexWidth() const { return mTexWidth; }
    
protected:
    SDL_Texture* mTexture;
    int mDrawOrder;
    int mTexWidth;
    int mTexHeight;
};

#endif /* SpriteComponent_hpp */
