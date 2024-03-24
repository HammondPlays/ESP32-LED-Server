#include <Arduino.h>
#include <hexagon.h>

class HexagonBuilder {
    public:
    HexagonBuilder();
    Hexagon* build(int, int);

    int* test(int);
};