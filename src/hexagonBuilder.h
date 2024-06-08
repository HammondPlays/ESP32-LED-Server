#ifndef HEXAGON_BUILDER_H
#define HEXAGON_BUILDER_H

#include <Arduino.h>
#include <hexagon.h>

class HexagonBuilder {
    public:
    HexagonBuilder();
    Hexagon* build(int, int);

    int* test(int);
};

#endif // HEXAGON_BUILDER_H
