#ifndef GUI_H
#define GUI_H

#include <Arduino.h>
#include <SPIFFS.h>
#include <config.h>

class Gui
{
public:
    static String index();
    static String config();
    static String styles();
    static String stylesMobile();
    static String mainApp();
    static String configApp();
};

#endif // GUI_H