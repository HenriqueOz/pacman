#include "ghost.h"
#include "config/config.h"
#include "entities/collider/collider.h"
#include "entities/entity.h"
#include "entities/utils/movement.h"
#include "game/controller/game_controller.h"
#include "vec/vec.h"
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_thread.h>
#include <SDL3/SDL_video.h>
#include <limits>
#include <vector>

Ghost::Ghost(Vec2 const &pos,
             Vec2 const &scatter,
             GhostType type,
             int startDelay,
             GameController *gameController,
             Entities *entitiesRegistry,
             InputManager *inputManager)
  : m_state(GhostStates::SPAWN)
  , m_currentTile(0, 0)
  , m_ghostType(type)
  , m_scatterTarget(scatter)
  , m_gameController(gameController)
  , m_entitiesRegistry(entitiesRegistry)
  , m_inputManager(inputManager)
  , m_direction(Utils::Direction::UP)
  , m_spawnOrigin(pos)
  , m_startDelay(startDelay)
  , m_currentTarget(m_spawnOrigin)
{
    m_speed = 1;
    m_position.update(pos);
    m_size.update(Config::tileWidth, Config::tileHeight);
    m_currentTile = Utils::positionToTiles(m_position);
    m_chaseTime = 1200;
    m_scatterTime = 300;
    m_baseSpeed = 1;
    m_eatenSpeed = 2;
    m_timer = m_startDelay;
}

void
Ghost::update()
{
    if (!m_gameController->pacmanExists()) {
        return;
    }

    if (m_inputManager->isKeyPressed(SDLK_1)) {
        m_state = GhostStates::EATEN;
    }

    switch (m_state) {
        case GhostStates::SPAWN:
            if (m_timer > 0) {
                m_timer--;
                return;
            }
            m_state = GhostStates::IDLE;
            break;
        case GhostStates::IDLE:
            handleIdleState();
            break;
        case GhostStates::CHASING:
            handleChasingState();
            break;
        case GhostStates::SCATTER:
            handleScatterState();
            break;
        case GhostStates::FRIGHTENED:
        case GhostStates::EATEN:
            handleEatenState();
            break;
    }

    const int directionValue = Utils::getDirectionValue(m_direction);
    const int finalSpeed = m_speed * directionValue;

    switch (m_direction) {
        case Utils::Direction::LEFT:
        case Utils::Direction::RIGHT:
            m_position.x += finalSpeed;
            break;
        case Utils::Direction::UP:
        case Utils::Direction::DOWN:
            m_position.y += finalSpeed;
            break;
        case Utils::Direction::UNDEFINED:
            break;
    }

    m_currentTile = Utils::positionToTiles(m_position);
    wrapOutOfBounds();
}

void
Ghost::render(SDL_Renderer *renderer) const
{
    SDL_FRect rect = { static_cast<float>(m_position.x),
                       static_cast<float>(m_position.y),
                       static_cast<float>(m_size.x),
                       static_cast<float>(m_size.y) };

    SDL_Color ghostColor = getGhostColor();
    SDL_SetRenderDrawColor(renderer, ghostColor.r, ghostColor.g, ghostColor.b, ghostColor.a);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    drawLineToTarget(renderer, m_currentTarget);

    SDL_SetRenderDrawColor(renderer, ghostColor.r, ghostColor.g, ghostColor.b, ghostColor.a);
    SDL_FRect target = { static_cast<float>(m_currentTarget.x),
                         static_cast<float>(m_currentTarget.y),
                         static_cast<float>(m_size.x),
                         static_cast<float>(m_size.y) };
    SDL_RenderRect(renderer, &target);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void
Ghost::handleIdleState()
{
    if (m_timer-- > 0) {
        return;
    }

    m_speed = m_baseSpeed;
    m_currentTarget = m_gameController->getGhostDoorExitPosition();
    setBestDirectionTo(m_currentTarget);

    if (m_position.equals(m_currentTarget)) {
        m_state = GhostStates::SCATTER;
        m_position = m_currentTarget;
    }
}

void
Ghost::setBestDirectionTo(Vec2 position)
{
    if (m_position.x % Config::tileWidth != 0 && m_position.y % Config::tileHeight != 0) {
        return;
    }

    const std::vector<Utils::Direction> directions = getAvailableDirections();

    if (directions.empty()) {
        return;
    }

    float shortestDistance = std::numeric_limits<float>::max();
    Utils::Direction finalDirection = directions[0];

    for (Utils::Direction direction : directions) {
        const Vec2 nextTilePos = Utils::getNextTilePositionAt(m_position, direction);
        const float distance = Utils::getManhattanDistance(nextTilePos, position);

        if (distance < shortestDistance) {
            finalDirection = direction;
            shortestDistance = distance;
        } else if (distance == shortestDistance) {
            if (m_state != GhostStates::EATEN &&
                getDirectionPriority(direction) > getDirectionPriority(finalDirection)) {
                finalDirection = direction;
            } else {
                finalDirection = direction;
            }
        }
    }

    m_direction = finalDirection;
}

std::vector<Utils::Direction>
Ghost::getAvailableDirections() const
{
    std::vector<Utils::Direction> directions;
    directions.reserve(4);

    const int xLeft = m_position.x;
    const int xRight = m_position.x + m_size.x - 1;
    const int yTop = m_position.y;
    const int yBottom = m_position.y + m_size.y - 1;
    const bool canPassThroughGhostDoor =
      (m_state == GhostStates::IDLE || m_state == GhostStates::EATEN);

    if (m_direction != Utils::Direction::RIGHT) {
        Collider *leftTopCollider =
          (Collider *)m_entitiesRegistry->getEntityAt(xLeft - m_speed, yTop, EntityType::COLLIDER);
        Collider *leftBottomCollider = (Collider *)m_entitiesRegistry->getEntityAt(
          xLeft - m_speed, yBottom, EntityType::COLLIDER);

        bool leftTopBlocked =
          leftTopCollider && !(canPassThroughGhostDoor && leftTopCollider->isGhostDoor());
        bool leftBottomBlocked =
          leftBottomCollider && !(canPassThroughGhostDoor && leftBottomCollider->isGhostDoor());

        if (!leftTopBlocked && !leftBottomBlocked) {
            directions.push_back(Utils::Direction::LEFT);
        }
    }

    if (m_direction != Utils::Direction::LEFT) {
        Collider *rightTopCollider =
          (Collider *)m_entitiesRegistry->getEntityAt(xRight + m_speed, yTop, EntityType::COLLIDER);
        Collider *rightBottomCollider = (Collider *)m_entitiesRegistry->getEntityAt(
          xRight + m_speed, yBottom, EntityType::COLLIDER);

        bool rightTopBlocked =
          rightTopCollider && !(canPassThroughGhostDoor && rightTopCollider->isGhostDoor());
        bool rightBottomBlocked =
          rightBottomCollider && !(canPassThroughGhostDoor && rightBottomCollider->isGhostDoor());

        if (!rightTopBlocked && !rightBottomBlocked) {
            directions.push_back(Utils::Direction::RIGHT);
        }
    }

    if (m_direction != Utils::Direction::DOWN) {
        Collider *upLeftCollider =
          (Collider *)m_entitiesRegistry->getEntityAt(xLeft, yTop - m_speed, EntityType::COLLIDER);
        Collider *upRightCollider =
          (Collider *)m_entitiesRegistry->getEntityAt(xRight, yTop - m_speed, EntityType::COLLIDER);

        bool upLeftBlocked =
          upLeftCollider && !(canPassThroughGhostDoor && upLeftCollider->isGhostDoor());
        bool upRightBlocked =
          upRightCollider && !(canPassThroughGhostDoor && upRightCollider->isGhostDoor());

        if (!upLeftBlocked && !upRightBlocked) {
            directions.push_back(Utils::Direction::UP);
        }
    }

    if (m_direction != Utils::Direction::UP) {
        Collider *downLeftCollider = (Collider *)m_entitiesRegistry->getEntityAt(
          xLeft, yBottom + m_speed, EntityType::COLLIDER);
        Collider *downRightCollider = (Collider *)m_entitiesRegistry->getEntityAt(
          xRight, yBottom + m_speed, EntityType::COLLIDER);

        bool downLeftBlocked =
          downLeftCollider && !(canPassThroughGhostDoor && downLeftCollider->isGhostDoor());
        bool downRightBlocked =
          downRightCollider && !(canPassThroughGhostDoor && downRightCollider->isGhostDoor());

        if (!downLeftBlocked && !downRightBlocked) {
            directions.push_back(Utils::Direction::DOWN);
        }
    }

    return directions;
}

void
Ghost::drawLineToTarget(SDL_Renderer *renderer, Vec2 target) const
{
    SDL_Color ghostColor = getGhostColor();
    SDL_SetRenderDrawColor(renderer, ghostColor.r, ghostColor.g, ghostColor.b, ghostColor.a);
    SDL_RenderLine(renderer, m_position.x, m_position.y, target.x, target.y);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void
Ghost::wrapOutOfBounds()
{
    const int width = Config::logicalWidth;
    const int height = Config::logicalHeight;
    const int ghostWidth = m_size.x;
    const int ghostHeight = m_size.y;

    if (m_position.x <= 0 - ghostWidth && m_direction == Utils::Direction::LEFT) {
        m_position.x = width - 1;
    } else if (m_position.x >= width && m_direction == Utils::Direction::RIGHT) {
        m_position.x = 0 - ghostWidth + 1;
    }
}

int
Ghost::getDirectionPriority(Utils::Direction direction) const
{
    switch (direction) {
        case Utils::Direction::UP:
            return 4;
        case Utils::Direction::LEFT:
            return 3;
        case Utils::Direction::DOWN:
            return 2;
        case Utils::Direction::RIGHT:
            return 1;
        default:
            return 0;
    }
}

void
Ghost::handleChasingState()
{
    m_speed = m_baseSpeed;
    m_currentTarget = getGhostChaseTarget();
    setBestDirectionTo(m_currentTarget);

    m_timer++;

    if (m_timer > m_chaseTime) {
        m_timer = 0;
        m_state = GhostStates::SCATTER;
    }
}

void
Ghost::handleScatterState()
{
    m_speed = m_baseSpeed;
    m_currentTarget = m_scatterTarget;
    setBestDirectionTo(m_currentTarget);

    if (m_timer++ <= m_scatterTime) {
        return;
    }

    m_timer = 0;

    Utils::Direction newDirection = getReverseDirection(m_direction);
    Vec2 nextDirectionTile = Utils::getNextTilePositionAt(m_position, newDirection);

    if (!m_entitiesRegistry->hasEntityAt(
          nextDirectionTile.x, nextDirectionTile.y, EntityType::COLLIDER)) {
        m_direction = newDirection;
    }

    m_state = GhostStates::CHASING;
}

void
Ghost::handleEatenState()
{
    if (m_speed == m_baseSpeed) {
        m_position = Utils::tilesToPosition(m_currentTile);
    }

    m_speed = m_eatenSpeed;
    m_currentTarget = m_spawnOrigin;
    setBestDirectionTo(m_currentTarget);

    if (Utils::getManhattanDistance(m_position, m_currentTarget) <= 12) {
        m_position = m_currentTarget;
        m_state = GhostStates::IDLE;
    }
}

SDL_Color
Ghost::getGhostColor() const
{
    switch (m_ghostType) {
        case GhostType::Blinky:
            return { .r = 255, .a = 255 };
        case GhostType::Pinky:
            return { .r = 255, .g = 192, .b = 203, .a = 255 };
        case GhostType::Inky:
            return { .r = 0, .g = 255, .b = 255, .a = 255 };
        case GhostType::Clyde:
            return { .r = 255, .g = 165, .b = 0, .a = 255 };
        default:
            return { .r = 255, .g = 255, .b = 255, .a = 255 };
    }
}

Vec2
Ghost::getGhostChaseTarget() const
{
    Vec2 pacmanPosition = m_gameController->getPacmanPosition();
    Vec2 pacmanTile = Utils::positionToTiles(pacmanPosition);
    Utils::Direction pacmanDirection = m_gameController->getPacmanFacingDirection();
    int pacmanDirectionValue = Utils::getDirectionValue(pacmanDirection);

    switch (m_ghostType) {
        case GhostType::Blinky:
            return pacmanPosition;
        case GhostType::Pinky:
            return getPinkyChasingTarget(pacmanPosition, pacmanDirection);
        case GhostType::Inky:
            return getInkyChasingTarget(pacmanPosition, pacmanDirection);
        case GhostType::Clyde:
            return pacmanPosition;
            break;
    }
    return { 0, 0 };
}

Vec2
Ghost::getPinkyChasingTarget(Vec2 pacmanPosition, Utils::Direction pacmanDirection) const
{
    Vec2 targetTile = Utils::positionToTiles(pacmanPosition);
    const int pacmanDirectionValue = Utils::getDirectionValue(pacmanDirection);
    const int offset = 4;

    if (pacmanDirection == Utils::Direction::LEFT || pacmanDirection == Utils::Direction::RIGHT) {
        targetTile.x += offset * pacmanDirectionValue;
    } else if (pacmanDirection == Utils::Direction::UP ||
               pacmanDirection == Utils::Direction::DOWN) {
        targetTile.y += offset * pacmanDirectionValue;
    }
    return Utils::tilesToPosition(targetTile);
}

Vec2
Ghost::getInkyChasingTarget(Vec2 pacmanPosition, Utils::Direction pacmanDirection) const
{
    Vec2 targetTile = Utils::positionToTiles(pacmanPosition);
    const int pacmanDirectionValue = Utils::getDirectionValue(pacmanDirection);
    const int offset = 1;

    if (pacmanDirection == Utils::Direction::LEFT || pacmanDirection == Utils::Direction::RIGHT) {
        targetTile.x += pacmanDirectionValue;
    } else if (pacmanDirection == Utils::Direction::UP ||
               pacmanDirection == Utils::Direction::DOWN) {
        targetTile.y += pacmanDirectionValue;
    }

    const Vec2 targetPosition = Utils::tilesToPosition(targetTile);
    const Vec2 blinkyPosition = m_gameController->getBlinkyPosition();
    const Vec2 diff = {
        blinkyPosition.x - targetPosition.x,
        blinkyPosition.y - targetPosition.y,
    };

    return {
        targetPosition.x - diff.x,
        targetPosition.y - diff.y,
    };
}