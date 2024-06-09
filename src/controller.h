#include <httpServer.h>
// #include <animationType.h>

class Controller {
  public:    
    static void index();
    static void ledSwitchOnOff();
    static void setBrightness(int brightness);
    static void setAnimationType(int animationType);
    static void notFound();
    static String SendHTML(uint8_t led1stat,uint8_t led2stat);
};