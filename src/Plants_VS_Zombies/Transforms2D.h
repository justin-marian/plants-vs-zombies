#pragma once

#include "utils/glm_utils.h"


namespace Transforms2D
{
    // Translate matrix MAT3
    inline glm::mat3 Translate(float translateX, float translateY)
    {
        return glm::transpose(glm::mat3(1, 0, translateX,
                                        0, 1, translateY,
                                        0, 0, 1));
    }

    // Scale matrix MAT3
    inline glm::mat3 Scale(float scaleX, float scaleY)
    {
        return glm::transpose(glm::mat3(scaleX, 0, 0,
                                        0, scaleY, 0,
                                        0, 0, 1));
    }

    // Rotate matrix MAT3
    inline glm::mat3 Rotate(float radians)
    {
        return glm::transpose(glm::mat3(cos(radians), -sin(radians), 0,
                                        sin(radians), cos(radians),  0,
                                        0,            0,             1));
    }
}   // namespace Transforms2D
