#ifndef HEXAGONANIMATION_H
#define HEXAGONANIMATION_H

#include "animation.h"
#include <hexagon.h>
#include <vector>

class HexagonAnimation : public Animation {
    public:
        HexagonAnimation(int, int, int);
        void boomerang() override;
        void rainbow() override;

    private:
        std::vector<Hexagon> hexagons;
};

#endif