#include <httpServer.h>

class Controller {
  public:    
    static void index();
    static void notFound();
    static String SendHTML(uint8_t led1stat,uint8_t led2stat);
};