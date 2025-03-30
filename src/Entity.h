#ifndef _ENTITY_H
#define _ENTITY_H

class Entity
{
  public:
    virtual ~Entity() {};
    virtual void update() = 0;
    virtual void render() const;

  protected:
    Entity() {};
};

#endif
