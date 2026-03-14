#ifndef HEXAGONANIMATION_H
#define HEXAGONANIMATION_H

#include "animation.h"
#include <shape.h>
#include <vector>

class ShapeAnimation : public Animation {
    public:
        ShapeAnimation(int, int, int);
        void boomerang() override;
        void rainbow() override;

    private:
        std::vector<Shapes> shapes;
};

#endif