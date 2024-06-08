#include "gui.h"

String Gui::style() {
    String style = "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    style += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
    style += ".home-button { position: absolute; top: 10px; left: 10px; background-image: url('https://img.icons8.com/?size=50&id=2797&format=png'); background-size: cover; width: 40px; height: 40px; display: inline-block; }\n";
    style += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    style += ".button-on {background-color: #3498db;}\n";
    style += ".button-on:active {background-color: #2980b9;}\n";
    style += ".button-off {background-color: #34495e;}\n";
    style += ".button-off:active {background-color: #2c3e50;}\n";
    style += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    style += "</style>\n";

    return style;
}

String Gui::index() {
    String ptr = "<!DOCTYPE html> <html>\n";
    ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
    ptr += "<title>LED Control</title>\n";
    ptr += Gui::style();
    ptr += "</head>\n";
    ptr += "<body>\n";
    ptr += "<a class=\"home-button\" href=\"/\">HOME</a>\n";
    ptr += "<h1>ESP32 Web Server</h1>\n";
    ptr += "<h3>Using Access Point(AP) Mode</h3>\n";
    
    ptr +="<p>LED Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">SWITCH</a>\n";

    ptr +="</body>\n";
    ptr +="</html>\n";
    return ptr;
}