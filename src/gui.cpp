#include "gui.h"

String Gui::head(String title)
{
    String ptr = "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
    ptr += "<title>" + title + "</title>\n";
    ptr += Gui::style();
    ptr += "</head>\n";
    return ptr;
}

String Gui::style()
{
    String style = "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    style += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
    style += ".home-button { position: absolute; top: 20px; left: 20px; background-image: url('https://img.icons8.com/?size=50&id=2797&format=png'); background-size: cover; width: 80x; height: 80px; display: inline-block; }\n";
    style += ".button {display: block;width: 120px; max-width: 120px; flex-basis: calc(100% / 3);background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 10px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    style += ".button-frame { display: inline-flex; justify-content: center; align-items: center; border: 2px solid #444; padding: 10px; margin: 10px 0; flex-wrap: wrap; gap: 10px; }\n";

    style += ".button-on {background-color: #3498db;}\n";
    style += ".button-on:active {background-color: #2980b9;}\n";
    style += ".button-off {background-color: #34495e;}\n";
    style += ".button-off:active {background-color: #2c3e50;}\n";

    style += "</style>\n";

    return style;
}

String Gui::index()
{
    String ptr = "<!DOCTYPE html> <html>\n";
    ptr += Gui::head("Home");

    ptr += "<body>\n";
    ptr += "<a class=\"home-button\" href=\"/\"></a>\n";
    ptr += "<h1>Home</h1>\n";
    ptr += "<h3>LED-Steuerung</h3>\n";

    ptr += "<p>LED Status: OFF</p>";

    ptr += "<a class=\"button button-on\" href=\"/led-state\">SWITCH</a>\n";
    ptr += "<input id=\"brightness_input\" type=\"range\" value=\"25\" step=\"1\" min=\"0\" max=\"100\" onchange=\"updateBrightness(this.value)\">\n";

    ptr += "<h3>Animations</h3>\n";
    ptr += "<div class=\"button-frame\">\n";
    ptr += "<form action=\"/animation/0\" method=\"post\"><input type=\"submit\" value=\"Boomerang\"/></form>\n";
    ptr += "<form action=\"/animation/1\" method=\"post\"><input type=\"submit\" value=\"Rainbow\"/></form>\n";
    ptr += "</div>\n";
    // ptr += "<p>Brightness: <output id=\"brightness\"></output></p>\n"; TODO: Not Working

    ptr += Gui::functions();
    ptr += "</body>\n";
    ptr += "</html>\n";
    return ptr;
}

String Gui::functions()
{
    String ptr = "<script>\n";
    ptr += "function updateBrightness(val) {\n";
    ptr += "var xhr = new XMLHttpRequest();\n";
    ptr += "xhr.open(\"PUT\", \"/brightness/\" + val, true);\n";

    ptr += "xhr.send();\n";
    ptr += "}\n";
    ptr += "</script>\n";

    ptr += "<script>\n";
    ptr += "function updateAnimation(val) {\n";
    ptr += "var xhr = new XMLHttpRequest();\n";
    ptr += "xhr.open(\"PUT\", \"/brightness/\" + val, true);\n";

    ptr += "xhr.send();\n";
    ptr += "}\n";
    ptr += "</script>\n";
    return ptr;
}