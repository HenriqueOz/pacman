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
Pacman::changeDirectionsByKeyPressed(SDL_Keycode keycode, Direction direction)
{
    if (!m_inputManager->isKeyPressed(keycode)) {
        return;
    }

    if (!canMoveTo(direction)) {
        return;
    }

    if (direction == Direction::LEFT || direction == Direction::RIGHT) {
        m_dirx = getDirectionValue(direction);
        m_diry = 0;
    } else if (direction == Direction::UP || direction == Direction::DOWN) {
        m_dirx = 0;
        m_diry = getDirectionValue(direction);
    }
}

void
Pacman::handleInput()
{
    changeDirectionsByKeyPressed(m_left, Direction::LEFT);
    changeDirectionsByKeyPressed(m_right, Direction::RIGHT);
    changeDirectionsByKeyPressed(m_up, Direction::UP);
    changeDirectionsByKeyPressed(m_down, Direction::DOWN);
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
Pacman::canMoveTo(Direction direction) const
{
    const int xLeft = m_position.x;
    const int xRight = m_position.x + m_size.x - 1;
    const int yTop = m_position.y;
    const int yBottom = m_position.y + m_size.y - 1;

    switch (direction) {
        case Direction::LEFT:
            return !hasColliderAt(xLeft - 1, yTop) && !hasColliderAt(xLeft - 1, yBottom);
        case Direction::RIGHT:
            return !hasColliderAt(xRight + 1, yTop) && !hasColliderAt(xRight + 1, yBottom);
        case Direction::UP:
            return !hasColliderAt(xLeft, yTop - 1) && !hasColliderAt(xRight, yTop - 1);
        case Direction::DOWN:
            return !hasColliderAt(xLeft, yBottom + 1) && !hasColliderAt(xRight, yBottom + 1);
        default:
            return false;
    }
}

void
Pacman::handleCollision(int pastDirX, int pastDirY)
{
    const bool isMovingHorizontally = m_dirx != 0;
    const bool isMovingVertically = m_diry != 0;

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

    if (isMovingHorizontally) {
        m_dirx = 0;
        m_diry = pastDirY;
    }

    if (isMovingVertically) {
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

    if (m_position.x < 0 - pacmanWidth && m_dirx == getDirectionValue(Direction::LEFT)) {
        m_position.x = width;
    } else if (m_position.x > width && m_dirx == getDirectionValue(Direction::RIGHT)) {
        m_position.x = 0 - pacmanWidth;
    } else if (m_position.y < 0 && m_diry == getDirectionValue(Direction::UP)) {
        m_position.y = height - pacmanHeight;
    } else if (m_position.y > height && m_diry == getDirectionValue(Direction::DOWN)) {
        m_position.y = 0;
    }
}

int
Pacman::getDirectionValue(Direction direction) const
{
    switch (direction) {
        case LEFT:
        case UP:
            return -1;
        case RIGHT:
        case DOWN:
            return 1;
    }
}