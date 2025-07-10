#include "entity.h"

void
Entity::setId(Uint32 id)
{
    if (m_idSet) {
        return;
    }

    m_id = id;
    m_idSet = true;
}

Uint32
Entity::getId()
{
    return m_id;
}
