#include "gui.h"

String readFile(String filename)
{
    File file = SPIFFS.open(filename, "r");

    if (!file)
    {
        String errorMessage = "Failed to open file " + filename;
        Serial.println(errorMessage);
        return errorMessage;
    }

    return file.readString();
}

String Gui::index()
{
    return readFile("/frontend/index.html");
}

String Gui::styles()
{
    return readFile("/frontend/styles-desktop.css");
}

String Gui::stylesMobile()
{
    return readFile("/frontend/styles-mobile.css");
}

String Gui::app()
{
    return readFile("/frontend/app.js");
}