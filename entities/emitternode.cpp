#include <entities/emitternode.hpp>
#include <entities/particlenode.hpp>

EmitterNode::EmitterNode(Particle::Type type) :
    SceneNode(),
    mAccumulatedTime(sf::Time::Zero),
    mType(type),
    mParticleSystem(nullptr)
{
}


void EmitterNode::emitCrateParticles()
{
    if(mParticleSystem == nullptr)    return;

    int nb_particles = 8;
    int angle = 360 / nb_particles;

    for(int i = 0; i < nb_particles; ++i)
    {
        mParticleSystem->addParticle(getWorldPosition(), i * angle);
    }
}

void EmitterNode::emitExposionParticles()
{
    if(mParticleSystem == nullptr)    return;

    int nb_particles = 36;
    int angle = 360 / nb_particles;

    for(int i = 0; i < nb_particles; ++i)
    {
        mParticleSystem->addParticle(getWorldPosition(), i * angle);
    }
}


void EmitterNode::updateCurrent(sf::Time dt, CommandQueue &commands)
{
    if(mParticleSystem)
    {
        if(mType == Particle::Trail)
        {
            emitParticles(dt);
        }
    }
    else
    {
        auto finder = [this](ParticleNode& container, sf::Time) {
            if(container.getParticleType() == mType)
                mParticleSystem = &container;
        };
        Command command;
        command.action = derivedAction<ParticleNode>(finder);
        command.category = Category::ParticleSystem;
        commands.push(command);
    }
}

void EmitterNode::emitParticles(sf::Time dt)
{
    const float emissionRate = 30.f;
    const sf::Time interval = sf::seconds(1.f) / emissionRate;

    mAccumulatedTime += dt;

    while(mAccumulatedTime > interval)
    {
        mAccumulatedTime -= interval;
        mParticleSystem->addParticle(getWorldPosition());
    }
}
