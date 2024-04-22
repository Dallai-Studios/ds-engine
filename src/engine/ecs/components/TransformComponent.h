#pragma once

#include <glm/glm.hpp>

#define DEF_POSITION glm::vec2(0.0, 0.0)
#define DEF_ROTATION 0.0
#define DEF_SCALE glm::vec2(1.0, 1.0)

struct TransformComponent {
    glm::vec2 position;
    double rotation;
    glm::vec2 scale;

    TransformComponent(glm::vec2 position = DEF_POSITION, double rotation = DEF_ROTATION, glm::vec2 scale = DEF_SCALE) {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
    }
};