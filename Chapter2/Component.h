//
// Created by muhammad chambers on 12/3/24.
//

#ifndef CHAPTER2_COMPONENT_H
#define CHAPTER2_COMPONENT_H


class Component {
public:
    Component(class Actor* owner, int updateOrder = 100);
    /** Destructor. */
    virtual ~Component();

    /** Update this component by delta time. */
    virtual void Update(float deltaTime);
    int GetUpdateOrder() const { return mUpdateOrder; }

protected:
    /** Owning actor. */
    class Actor* mOwner;
    /** Update order of component. */
    int mUpdateOrder;

};


#endif //CHAPTER2_COMPONENT_H
