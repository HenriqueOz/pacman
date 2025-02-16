#ifndef ENTITY_H
#define ENTITY_H

#include <cstddef>

typedef std::size_t Entity;

inline const Entity
create_entity()
{
    static Entity lastId = 0;
    return ++lastId;
};

#endif
