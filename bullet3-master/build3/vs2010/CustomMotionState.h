#pragma once
#include <btBulletDynamicsCommon.h>

class MyMotionState : public btMotionState {
public:
    MyMotionState(const btTransform& initialTransform)
        : m_transform(initialTransform) {}

    // Called by Bullet to get the world transform
    void getWorldTransform(btTransform& worldTrans) const override {
        worldTrans = m_transform;
    }

    // Called by Bullet to update the world transform
    void setWorldTransform(const btTransform& worldTrans) override {
        m_transform = worldTrans;
    }

    const btTransform& getTransform() const {
        return m_transform;
    }

    void setTransform(const btTransform& transform) {
        m_transform = transform;
    }

private:
    btTransform m_transform;
};