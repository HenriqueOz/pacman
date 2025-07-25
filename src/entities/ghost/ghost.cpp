#include "ghost.h"
#include "config/config.h"
#include "entities/collider/collider.h"
#include "entities/entity.h"
#include "entities/utils/utils.h"
#include "registry/controller/game_controller.h"
#include "registry/registry.h"
#include "vec/vec.h"
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_thread.h>
#include <SDL3/SDL_video.h>
#include <cmath>
#include <limits>
#include <vector>

Ghost::Ghost(Vec2 const &pos)
  : m_state(GhostStates::IDLE)
  , m_currentTile(0, 0)
  , m_gameController(Registry::getGameController())
  , m_entitiesRegistry(Registry::getEntitiesRegistry())
  , m_direction(Utils::Direction::DOWN)
  , m_spawnOrigin(pos)
  , m_currentTarget(m_spawnOrigin)
{
    m_speed = 1;
    m_position.update(pos);
    m_size.update(Config::tileWidth, Config::tileHeight);
    m_currentTile = Utils::fixPositionToGrid(m_position);
}

void
Ghost::update()
{
    if (!m_gameController->pacmanExists()) {
        return;
    }

    if (Registry::getInputManager()->isKeyPressed(SDLK_1)) {
        m_state = GhostStates::EATEN;
    }

    switch (m_state) {
        case GhostStates::IDLE:
            exitSpawn();
            break;
        case GhostStates::CHASING:
            m_currentTarget = m_gameController->getPacmanPosition();
            setBestDirectionTo(m_currentTarget);
            break;
        case GhostStates::SCATTER:
        case GhostStates::FRIGHTENED:
        case GhostStates::EATEN:
            // TODO remove this test here and implement eaten state properly
            if (m_speed == 1) {
                m_position = Utils::gridPositionToReal(m_currentTile);
            }

            m_speed = 2;
            m_currentTarget = m_spawnOrigin;
            setBestDirectionTo(m_currentTarget);

            if (getManhattanDistance(m_position, m_currentTarget) < 12) {
                m_position.update(m_currentTarget);
            }

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
    }

    m_currentTile = Utils::fixPositionToGrid(m_position);
    wrapOutOfBounds();
}

void
Ghost::render(SDL_Renderer *renderer) const
{
    SDL_FRect rect = { static_cast<float>(m_position.x),
                       static_cast<float>(m_position.y),
                       static_cast<float>(m_size.x),
                       static_cast<float>(m_size.y) };

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    drawLineToTarget(renderer, m_currentTarget);
}

void
Ghost::exitSpawn()
{
    m_currentTarget = m_gameController->getGhostDoorExitPosition();
    setBestDirectionTo(m_currentTarget);

    if (m_position.equals(m_currentTarget)) {
        m_state = GhostStates::CHASING;
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
        const Vec2 nextTilePos = getTilePositionAt(direction);
        const float distance = getManhattanDistance(nextTilePos, position);

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

    const int xLeft = m_position.x;
    const int xRight = m_position.x + m_size.x - 1;
    const int yTop = m_position.y;
    const int yBottom = m_position.y + m_size.y - 1;
    const bool canPassThroughGhostDoors =
      (m_state == GhostStates::IDLE || m_state == GhostStates::EATEN);

    if (m_direction != Utils::Direction::RIGHT) {
        Collider *leftTopCollider =
          (Collider *)m_entitiesRegistry->getEntityAt(xLeft - m_speed, yTop, EntityType::COLLIDER);
        Collider *leftBottomCollider = (Collider *)m_entitiesRegistry->getEntityAt(
          xLeft - m_speed, yBottom, EntityType::COLLIDER);

        bool leftTopBlocked =
          leftTopCollider && !(canPassThroughGhostDoors && leftTopCollider->isGhostDoor());
        bool leftBottomBlocked =
          leftBottomCollider && !(canPassThroughGhostDoors && leftBottomCollider->isGhostDoor());

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
          rightTopCollider && !(canPassThroughGhostDoors && rightTopCollider->isGhostDoor());
        bool rightBottomBlocked =
          rightBottomCollider && !(canPassThroughGhostDoors && rightBottomCollider->isGhostDoor());

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
          upLeftCollider && !(canPassThroughGhostDoors && upLeftCollider->isGhostDoor());
        bool upRightBlocked =
          upRightCollider && !(canPassThroughGhostDoors && upRightCollider->isGhostDoor());

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
          downLeftCollider && !(canPassThroughGhostDoors && downLeftCollider->isGhostDoor());
        bool downRightBlocked =
          downRightCollider && !(canPassThroughGhostDoors && downRightCollider->isGhostDoor());

        if (!downLeftBlocked && !downRightBlocked) {
            directions.push_back(Utils::Direction::DOWN);
        }
    }

    return directions;
}

Vec2
Ghost::getTilePositionAt(Utils::Direction direction) const
{
    switch (direction) {
        case Utils::Direction::UP:
            return Utils::gridPositionToReal(Vec2(m_currentTile.x, m_currentTile.y - 1));
        case Utils::Direction::DOWN:
            return Utils::gridPositionToReal(Vec2(m_currentTile.x, m_currentTile.y + 1));
        case Utils::Direction::LEFT:
            return Utils::gridPositionToReal(Vec2(m_currentTile.x - 1, m_currentTile.y));
        case Utils::Direction::RIGHT:
            return Utils::gridPositionToReal(Vec2(m_currentTile.x + 1, m_currentTile.y));
        default:
            return Vec2(0, 0);
    }
}

float
Ghost::getDotsDistance(Vec2 a, Vec2 b) const
{
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

float
Ghost::getManhattanDistance(Vec2 a, Vec2 b) const
{
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

void
Ghost::drawLineToTarget(SDL_Renderer *renderer, Vec2 target) const
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
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
