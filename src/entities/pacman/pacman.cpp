#include "pacman.h"
#include "entities/entity.h"
#include "registry/registry.h"
#include <config/config.h>

Pacman::Pacman(Vec2 const &pos)
  : m_velocity(0.f, 0.f)
  , m_PacmanState(IDLE)
  , m_speed(1)
  , m_dirx(0)
  , m_diry(0)
{
    m_size.update(Config::tileWidth, Config::tileHeight);
    m_position.update(pos);
    m_position.x += m_size.x / 2;

    m_inputManager = Registry::getInputManager();
    m_entitiesRegistry = Registry::getEntitiesRegistry();
}

void
Pacman::update()
{
    switch (m_PacmanState) {
        case IDLE:
            idle();
            break;
        case MOVING:
            moving();
            break;
        case DEAD:
            break;
    }
}

void
Pacman::render(SDL_Renderer *renderer) const
{
    SDL_FRect rect = { static_cast<float>(m_position.x),
                       static_cast<float>(m_position.y),
                       static_cast<float>(m_size.x),
                       static_cast<float>(m_size.y) };

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void
Pacman::changeDirectionsByKeyPressed(SDL_Keycode keycode, Utils::Direction direction)
{
    if (!m_inputManager->isKeyPressed(keycode)) {
        return;
    }

    if (!canMoveTo(direction)) {
        return;
    }

    switch (direction) {
        case Utils::Direction::UP:
        case Utils::Direction::DOWN:
            m_dirx = 0;
            m_diry = Utils::getDirectionValue(direction);
            break;
        case Utils::Direction::LEFT:
        case Utils::Direction::RIGHT:
            m_dirx = Utils::getDirectionValue(direction);
            m_diry = 0;
            break;
    }
}

void
Pacman::handleInput()
{
    changeDirectionsByKeyPressed(m_left, Utils::Direction::LEFT);
    changeDirectionsByKeyPressed(m_right, Utils::Direction::RIGHT);
    changeDirectionsByKeyPressed(m_up, Utils::Direction::UP);
    changeDirectionsByKeyPressed(m_down, Utils::Direction::DOWN);
}

void
Pacman::idle()
{
    handleInput();

    if (m_dirx != 0 || m_diry != 0) {
        m_velocity.update(static_cast<float>(m_speed));
        m_PacmanState = MOVING;
    }
}

void
Pacman::moving()
{
    int pastDirX = m_dirx;
    int pastDirY = m_diry;

    handleInput();
    handleCollision(pastDirX, pastDirY);
    handleFoodEating();
    wrapOutOfBounds();

    m_position.x += m_dirx * m_velocity.x;
    m_position.y += m_diry * m_velocity.y;
}

bool
Pacman::canMoveTo(Utils::Direction direction) const
{
    const int xLeft = m_position.x;
    const int xRight = m_position.x + m_size.x - 1;
    const int yTop = m_position.y;
    const int yBottom = m_position.y + m_size.y - 1;

    switch (direction) {
        case Utils::Direction::LEFT:
            return !hasColliderAt(xLeft - 1, yTop) && !hasColliderAt(xLeft - 1, yBottom);
        case Utils::Direction::RIGHT:
            return !hasColliderAt(xRight + 1, yTop) && !hasColliderAt(xRight + 1, yBottom);
        case Utils::Direction::UP:
            return !hasColliderAt(xLeft, yTop - 1) && !hasColliderAt(xRight, yTop - 1);
        case Utils::Direction::DOWN:
            return !hasColliderAt(xLeft, yBottom + 1) && !hasColliderAt(xRight, yBottom + 1);
        default:
            return false;
    }
}

void
Pacman::handleCollision(int pastDirX, int pastDirY)
{
    const int xLeft = m_position.x;
    const int xRight = m_position.x + m_size.x - 1;
    const int yTop = m_position.y;
    const int yBottom = m_position.y + m_size.y - 1;

    const bool leftTop = hasColliderAt(xLeft + m_dirx, yTop + m_diry);
    const bool rightTop = hasColliderAt(xRight + m_dirx, yTop + m_diry);
    const bool leftBottom = hasColliderAt(xLeft + m_dirx, yBottom + m_diry);
    const bool rightBottom = hasColliderAt(xRight + m_dirx, yBottom + m_diry);

    const bool hasCollision = leftTop || rightTop || leftBottom || rightBottom;

    if (!hasCollision) {
        return;
    }

    if (m_dirx != 0) {
        m_dirx = 0;
        m_diry = pastDirY;
    }

    if (m_diry != 0) {
        m_dirx = pastDirX;
        m_diry = 0;
    }
}

bool
Pacman::hasColliderAt(int x, int y) const
{
    return m_entitiesRegistry->hasEntityAt(x, y, EntityType::COLLIDER);
}

void
Pacman::handleFoodEating()
{
    if (m_entitiesRegistry->hasEntityAt(m_position.x, m_position.y, EntityType::FOOD)) {
        m_entitiesRegistry->deleteEntityAt(m_position.x, m_position.y, EntityType::FOOD);
    }
}

void
Pacman::wrapOutOfBounds()
{
    const int width = Config::logicalWidth;
    const int height = Config::logicalHeight;
    const int pacmanWidth = m_size.x;
    const int pacmanHeight = m_size.y;

    if (m_position.x < 0 - pacmanWidth &&
        m_dirx == Utils::getDirectionValue(Utils::Direction::LEFT)) {
        m_position.x = width;
    } else if (m_position.x > width &&
               m_dirx == Utils::getDirectionValue(Utils::Direction::RIGHT)) {
        m_position.x = 0 - pacmanWidth;
    } else if (m_position.y < 0 && m_diry == Utils::getDirectionValue(Utils::Direction::UP)) {
        m_position.y = height - pacmanHeight;
    } else if (m_position.y > height &&
               m_diry == Utils::getDirectionValue(Utils::Direction::DOWN)) {
        m_position.y = 0;
    }
}