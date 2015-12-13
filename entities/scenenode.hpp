#ifndef SCENENODE_H
#define SCENENODE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <set>
#include <memory>
#include <cassert>

#include <events/commandqueue.hpp>
#include <resources/resourceidentifiers.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
    typedef std::unique_ptr<SceneNode> Ptr;
    typedef std::pair<SceneNode*, SceneNode*> Pair;

public:
    explicit SceneNode(Category::Type category = Category::None);

    void                    attachChild(Ptr child);
    Ptr                     detachChild(const SceneNode& node);

    void                    update(sf::Time dt, CommandQueue& commands);
    void                    removeWrecks();

    virtual bool            isMarkedForRemoval() const;
    virtual bool            isCollidable() const;
    virtual bool            isDestroyed() const { return false; }
    void                    checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
    void                    checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);

    void                    playLocalSound(CommandQueue& commands, Sounds::ID sound);

    sf::Transform           getWorldTransform() const;
    sf::Vector2f            getWorldPosition() const;
    virtual sf::FloatRect   getBoundingRect() const;

    virtual unsigned int    getCategory() const;
    void                    onCommand(const Command& command, sf::Time dt);

private:
    virtual void    updateCurrent(sf::Time dt, CommandQueue& commands);
    virtual void    updateChildren(sf::Time dt, CommandQueue& commands);

    virtual void    draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void    drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void    drawChildren(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    std::vector<Ptr>        mChildren;
    SceneNode*              mParent;

    Category::Type          mDefaultCategory;
};

#endif // SCENENODE_H
