#include "hexagonBuilder.h"

HexagonBuilder::HexagonBuilder() {

}

Hexagon* HexagonBuilder::build(int hexagonCount, int ledCountPerHexagon) {
    Hexagon *list = new Hexagon[hexagonCount];
    
    for (int i = 0; i < hexagonCount; i++)
    {
        list[i] = Hexagon(i, ledCountPerHexagon);
    }
    
    return list;
}