#ifndef GUI_H
#define GUI_H

#include <Arduino.h>
#include <config.h>

class Gui
{
public:
    static String head(String title);
    static String style();
    static String index();
    static String functions();
};

#endif // GUI_H