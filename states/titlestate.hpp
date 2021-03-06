#ifndef TITLESTATE_H
#define TITLESTATE_H

#include <SFML/Graphics.hpp>
#include <resources/bloomeffect.hpp>

#include <states/state.hpp>

class TitleState : public State
{
public:
    TitleState(StateStack& stack, Context context);
    virtual void        draw();
    virtual bool        update(sf::Time dt);
    virtual bool        handleEvent(const sf::Event &event);

private:
    sf::Text            mTitle;
    int                 mTitleOpacity;
    sf::Sprite          mBackground;
    sf::Sprite          mShip;
    sf::Sprite          mTrail;
    sf::Time            mTextEffectTime;
    sf::Sprite          mLogo;
    sf::Text            mLogoText;

    sf::RenderTexture   mSceneTexture;
    BloomEffect         mBloomEffect;

};

#endif // TITLESTATE_H
